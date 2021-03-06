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

#include "edit_enum_property.h"
#include "properties/forwards.h"
#include "frame_manager.h"

#include <ros/console.h>

#include <tf/transform_listener.h>

namespace rviz
{

IMPLEMENT_DYNAMIC_CLASS(EditEnumPGEditor, wxPGComboBoxEditor);
IMPLEMENT_DYNAMIC_CLASS(EditEnumPGProperty, wxEditEnumProperty);

EditEnumPGEditor::EditEnumPGEditor()
{

}

EditEnumPGEditor::EditEnumPGEditor(const EditEnumOptionCallback& cb)
: option_cb_(cb)
{

}

wxPGWindowList EditEnumPGEditor::CreateControls(wxPropertyGrid *propgrid, wxPGProperty *property, const wxPoint &pos, const wxSize &size) const
{
  if (option_cb_)
  {
    unsigned int len = property->GetChoices().GetCount();
    for(int i=0; i < len; ++i)
      property->DeleteChoice(i);

    V_string choices;
    option_cb_(choices);
    V_string::iterator it = choices.begin();
    V_string::iterator end = choices.end();
    for (; it != end; ++it)
    {
      const std::string& choice = *it;
      if (choice.empty())
      {
        continue;
      }

      property->InsertChoice(wxString::FromAscii(choice.c_str()), wxNOT_FOUND);
    }
  }

  return wxPGComboBoxEditor::CreateControls(propgrid, property, pos, size);
}

EditEnumPGProperty::EditEnumPGProperty()
{

}

EditEnumPGProperty::EditEnumPGProperty(const wxString& label, const wxString& name, const wxString& value )
: wxEditEnumProperty( label, name )
{
  SetValue(value);
}

} // namespace rviz

