/*
 * Copyright (c) 2009, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "plugin.h"
#include "type_registry.h"

#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include <ros/console.h>
#include <ros/package.h>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace rviz
{

Plugin::Plugin()
: loaded_(false)
, auto_load_(true)
, auto_load_tried_(false)
, doc_(0)
{

}

Plugin::~Plugin()
{
  unload();

  delete doc_;
}

void Plugin::loadDescription(const std::string& description_path)
{
  description_path_ = description_path;

  std::ifstream fin(description_path.c_str());

  try
  {
    YAML::Parser parser(fin);
    doc_ = new YAML::Node;
    YAML::Node& doc = *doc_;
    parser.GetNextDocument(doc);

    std::string library;
    doc["library"] >> library;

    fs::path p(description_path);
    fs::path parent = p.parent_path();
    // figure out the package this plugin is part of
    while (true)
    {
      if (fs::exists(parent / "manifest.xml"))
      {
        std::string package = parent.filename();
        std::string package_path = ros::package::getPath(package);
        if (description_path.find(package_path) == 0)
        {
          package_name_ = package;
          break;
        }
      }

      parent = parent.parent_path();

      if (parent.string().empty())
      {
        ROS_ERROR("Could not find package name for plugin [%s]", description_path.c_str());
        break;
      }
    }

    library_path_ = (p.parent_path() / fs::path((const char*)wxDynamicLibrary::CanonicalizeName(wxString::FromAscii(library.c_str()), wxDL_LIBRARY).char_str())).string();

    // wxMac returns .bundle, we want .so for now (until I figure out how to get cmake to build bundles)
#if __WXMAC__
    fs::path mac_path(library_path_);
    mac_path.replace_extension(".so");
    library_path_ = mac_path.string();
#endif

    doc["name"] >> name_;

    const YAML::Node& displays = doc["displays"];
    for (uint32_t i = 0; i < displays.size(); ++i)
    {
      const YAML::Node& n = displays[i];
      DisplayTypeInfoPtr info(new DisplayTypeInfo);
      info->package = package_name_;

      //n.Write(std::cout, 0, true, false);

      n["class_name"] >> info->class_name;
      n["display_name"] >> info->display_name;
      n["description"] >> info->help_description;

      display_info_.push_back(info);
    }

    // find old display class name mappings
    try
    {
      const YAML::Node& n = doc["display_class_mapping"];
      for (uint32_t i = 0; i < n.size(); ++i)
      {
        const YAML::Node& mapping = n[i];
        std::string old_class, new_class;
        mapping["old_class"] >> old_class;
        mapping["new_class"] >> new_class;
        display_class_mappings_[old_class] = new_class;
      }
    }
    catch (YAML::RepresentationException& e)
    {
    }

    // find old display name mappings
    try
    {
      const YAML::Node& n = doc["display_name_mapping"];
      for (uint32_t i = 0; i < n.size(); ++i)
      {
        const YAML::Node& mapping = n[i];
        std::string old_class, new_class;
        mapping["old_name"] >> old_class;
        mapping["new_name"] >> new_class;
        display_name_mappings_[old_class] = new_class;
      }
    }
    catch (YAML::RepresentationException& e)
    {
    }
  }
  catch (YAML::ParserException& e)
  {
    throw PluginParseException(description_path, e.msg);
  }
  catch (YAML::RepresentationException& e)
  {
    throw PluginParseException(description_path, e.msg);
  }
}

void Plugin::load()
{
  if (loaded_)
  {
    return;
  }

  loading_signal_(PluginStatus(this));

  if (!fs::exists(library_path_))
  {
    throw LibraryDoesNotExistException(library_path_);
  }

  if (!library_.Load(wxString::FromAscii(library_path_.c_str())))
  {
    throw UnableToLoadLibraryException(library_path_);
  }

  if (!library_.HasSymbol(wxT("rvizPluginInit")))
  {
    throw NoPluginInitFunctionException(library_path_);
  }

  typedef void (*InitFunc)(TypeRegistry*);
  InitFunc init = reinterpret_cast<InitFunc>(library_.GetSymbol(wxT("rvizPluginInit")));

  TypeRegistry reg;
  (*init)(&reg);

  {
    L_DisplayEntry::const_iterator it = reg.getDisplayEntries().begin();
    L_DisplayEntry::const_iterator end = reg.getDisplayEntries().end();
    for (; it != end; ++it)
    {
      const DisplayEntry& ent = *it;
      DisplayTypeInfoPtr info = getDisplayTypeInfo(ent.class_name);
      if (!info)
      {
        ROS_ERROR("Display with class name [%s] did not exist in the plugin yaml file.", ent.class_name.c_str());
        info.reset(new DisplayTypeInfo);
        info->class_name = ent.class_name;
      }

      if (info->display_name.empty())
      {
        info->display_name = info->class_name;
      }

      info->creator = ent.creator;
    }
  }

  {
    M_ClassEntry::const_iterator it = reg.getClassEntries().begin();
    M_ClassEntry::const_iterator end = reg.getClassEntries().end();
    for (; it != end; ++it)
    {
      const std::string& base_class = it->first;
      const L_ClassEntry& entries = it->second;
      L_ClassEntry::const_iterator ent_it = entries.begin();
      L_ClassEntry::const_iterator ent_end = entries.end();
      for (; ent_it != ent_end; ++ent_it)
      {
        const ClassEntry& ent = *ent_it;
        ClassTypeInfoPtr info(new ClassTypeInfo);
        info->base_class_name = base_class;
        info->class_name = ent.class_name;
        info->readable_name = ent.readable_name;
        info->creator = ent.creator;
        info->package = package_name_;
        class_info_[base_class].push_back(info);
      }
    }
  }

  loaded_ = true;
  loaded_signal_(PluginStatus(this));
}

const L_ClassTypeInfo* Plugin::getClassTypeInfoList(const std::string& base_class) const
{
  M_ClassTypeInfo::const_iterator it = class_info_.find(base_class);
  if (it == class_info_.end())
  {
    return 0;
  }

  return &it->second;
}

void Plugin::unload()
{
  if (!loaded_)
  {
    return;
  }

  unloading_signal_(PluginStatus(this));

  {
    L_DisplayTypeInfo::iterator it = display_info_.begin();
    L_DisplayTypeInfo::iterator end = display_info_.end();
    for (; it != end; ++it)
    {
      (*it)->creator.reset();
    }
  }

  class_info_.clear();

  library_.Unload();
  loaded_ = false;

  unloaded_signal_(PluginStatus(this));
}

bool Plugin::isLoaded()
{
  return loaded_;
}

bool Plugin::isAutoLoad()
{
  return auto_load_;
}

void Plugin::setAutoLoad(bool autoload)
{
  auto_load_ = autoload;
}

const std::string& Plugin::mapDisplayClassName(const std::string& class_name) const
{
  M_string::const_iterator it = display_class_mappings_.find(class_name);
  if (it == display_class_mappings_.end())
  {
    return class_name;
  }

  return it->second;
}

DisplayTypeInfoPtr Plugin::getDisplayTypeInfo(const std::string& class_name) const
{
  std::string mapped_name = mapDisplayClassName(class_name);
  L_DisplayTypeInfo::const_iterator it = display_info_.begin();
  L_DisplayTypeInfo::const_iterator end = display_info_.end();
  for (; it != end; ++it)
  {
    const DisplayTypeInfoPtr& info = *it;
    if (info->class_name == mapped_name)
    {
      return info;
    }
  }

  return DisplayTypeInfoPtr();
}

const std::string& Plugin::mapDisplayName(const std::string& name) const
{
  M_string::const_iterator it = display_name_mappings_.find(name);
  if (it == display_name_mappings_.end())
  {
    return name;
  }

  return it->second;
}

DisplayTypeInfoPtr Plugin::getDisplayTypeInfoByDisplayName(const std::string& display_name) const
{
  std::string mapped_name = mapDisplayName(display_name);
  L_DisplayTypeInfo::const_iterator it = display_info_.begin();
  L_DisplayTypeInfo::const_iterator end = display_info_.end();
  for (; it != end; ++it)
  {
    const DisplayTypeInfoPtr& info = *it;
    if (info->display_name == mapped_name)
    {
      return info;
    }
  }

  return DisplayTypeInfoPtr();
}

void Plugin::autoLoad()
{
  if (auto_load_tried_ || loaded_ || !auto_load_)
  {
    return;
  }

  try
  {
    load();
  }
  catch (LibraryDoesNotExistException&)
  {
  }
  catch (std::runtime_error& e)
  {
    ROS_ERROR("%s", e.what());
  }
}

Display* Plugin::createDisplay(const std::string& class_name, const std::string& name, VisualizationManager* manager)
{
  autoLoad();

  DisplayTypeInfoPtr typeinfo = getDisplayTypeInfo(class_name);
  if (!typeinfo || !typeinfo->creator)
  {
    return 0;
  }

  return typeinfo->creator->create(name, manager);
}

}
