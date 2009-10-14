/*
 * Copyright (c) 2008, Willow Garage, Inc.
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

#ifndef RVIZ_PROPERTY_FORWARDS_H
#define RVIZ_PROPERTY_FORWARDS_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/function.hpp>

namespace rviz
{

typedef boost::function<void(const std::string&)> StatusCallback;

class PropertyManager;

#define PROPERTY_FORWARD(name) \
  class name; \
  typedef boost::shared_ptr<name> name##Ptr; \
  typedef boost::weak_ptr<name> name##WPtr;

PROPERTY_FORWARD(PropertyBase);
PROPERTY_FORWARD(BoolProperty);
PROPERTY_FORWARD(IntProperty);
PROPERTY_FORWARD(FloatProperty);
PROPERTY_FORWARD(DoubleProperty);
PROPERTY_FORWARD(StringProperty);
PROPERTY_FORWARD(ColorProperty);
PROPERTY_FORWARD(EnumProperty);
PROPERTY_FORWARD(EditEnumProperty);
PROPERTY_FORWARD(CategoryProperty);
PROPERTY_FORWARD(Vector3Property);
PROPERTY_FORWARD(QuaternionProperty);
PROPERTY_FORWARD(ROSTopicStringProperty);
PROPERTY_FORWARD(StatusProperty);

template<class T>
void propertyChanged(boost::weak_ptr<T>& wprop)
{
  if (boost::shared_ptr<T> prop = wprop.lock())
  {
    prop->changed();
  }
}

template<class T>
void hideProperty(boost::weak_ptr<T>& wprop)
{
  if (boost::shared_ptr<T> prop = wprop.lock())
  {
    prop->hide();
  }
}

template<class T>
void showProperty(boost::weak_ptr<T>& wprop)
{
  if (boost::shared_ptr<T> prop = wprop.lock())
  {
    prop->show();
  }
}

} // namespace rviz

#endif

