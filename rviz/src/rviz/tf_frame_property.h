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

#ifndef RVIZ_TF_FRAME_PROPERTY_H
#define RVIZ_TF_FRAME_PROPERTY_H

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/editors.h>

#include <string>

namespace ros
{
class Node;
}

namespace rviz
{

class TFFramePGEditor : public wxPGComboBoxEditor
{
  DECLARE_DYNAMIC_CLASS(TFFramePGEditor);
public:
  TFFramePGEditor();
  virtual wxPGWindowList CreateControls(wxPropertyGrid *propgrid, wxPGProperty *property, const wxPoint &pos, const wxSize &size) const;
};

class TFFramePGProperty : public wxEditEnumProperty
{
  DECLARE_DYNAMIC_CLASS(TFFramePGProperty);
public:

  // Normal property constructor.
  TFFramePGProperty(const wxString& label, const wxString& name = wxPG_LABEL, const wxString& value = wxEmptyString);

  virtual const wxPGEditor* DoGetEditorClass () const { return new TFFramePGEditor; }

protected:
  TFFramePGProperty();
};

} // namespace rviz

#endif
