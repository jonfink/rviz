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

#ifndef RVIZ_TYPE_REGISTRY_H
#define RVIZ_TYPE_REGISTRY_H

#include <list>
#include <map>

#include <boost/shared_ptr.hpp>

#include "display_creator.h"

namespace rviz
{

class ClassCreator
{
public:
  virtual ~ClassCreator() {}
  virtual void* create() = 0;
};

template<typename T>
class ClassCreatorT : public ClassCreator
{
public:
  virtual void* create()
  {
    return new T;
  }
};
typedef boost::shared_ptr<ClassCreator> ClassCreatorPtr;

class DisplayCreator;
typedef boost::shared_ptr<DisplayCreator> DisplayCreatorPtr;

struct DisplayEntry
{
  DisplayCreatorPtr creator;
  std::string class_name;
};
typedef std::list<DisplayEntry> L_DisplayEntry;

struct ClassEntry
{
  ClassCreatorPtr creator;
  std::string class_name;
  std::string readable_name;
};
typedef std::list<ClassEntry> L_ClassEntry;
typedef std::map<std::string, L_ClassEntry> M_ClassEntry;

typedef std::map<std::string, std::string> M_string;

class TypeRegistry
{
public:
  template<class D>
  void registerDisplay(const std::string& class_name)
  {
    DisplayCreatorPtr creator(new DisplayCreatorT<D>);
    DisplayEntry ent;
    ent.creator = creator;
    ent.class_name = class_name;
    display_entries_.push_back(ent);
  }

  const L_DisplayEntry& getDisplayEntries() const { return display_entries_; }
  const M_ClassEntry& getClassEntries() const { return class_entries_; }

  template<class T>
  void registerClass(const std::string& class_type, const std::string& class_name, const std::string& readable_name)
  {
    ClassCreatorPtr creator(new ClassCreatorT<T>);
    ClassEntry ent;
    ent.creator = creator;
    ent.class_name = class_name;
    ent.readable_name = readable_name;
    class_entries_[class_type].push_back(ent);
  }

private:
  L_DisplayEntry display_entries_;
  M_ClassEntry class_entries_;
};

}

#endif
