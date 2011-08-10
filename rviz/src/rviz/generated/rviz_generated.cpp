///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "rviz_generated.h"

///////////////////////////////////////////////////////////////////////////

DisplaysPanelGenerated::DisplaysPanelGenerated( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	properties_panel_ = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	properties_panel_sizer_ = new wxBoxSizer( wxVERTICAL );
	
	properties_panel_->SetSizer( properties_panel_sizer_ );
	properties_panel_->Layout();
	properties_panel_sizer_->Fit( properties_panel_ );
	bSizer8->Add( properties_panel_, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	help_html_ = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	help_html_->SetBackgroundColour( wxColour( 239, 235, 231 ) );
	help_html_->SetMinSize( wxSize( -1,100 ) );
	
	sbSizer3->Add( help_html_, 1, wxALL|wxEXPAND, 5 );
	
	bSizer8->Add( sbSizer3, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	new_display_ = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	new_display_->SetToolTip( wxT("Add a new display") );
	
	bSizer7->Add( new_display_, 0, wxALL, 5 );
	
	delete_display_ = new wxButton( this, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	delete_display_->SetToolTip( wxT("Remove the selected display") );
	
	bSizer7->Add( delete_display_, 0, wxALL, 5 );
	
	manage_ = new wxButton( this, wxID_ANY, wxT("Manage..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( manage_, 0, wxALL, 5 );
	
	bSizer8->Add( bSizer7, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer8 );
	this->Layout();
	
	// Connect Events
	new_display_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DisplaysPanelGenerated::onNewDisplay ), NULL, this );
	delete_display_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DisplaysPanelGenerated::onDeleteDisplay ), NULL, this );
	manage_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DisplaysPanelGenerated::onManage ), NULL, this );
}

DisplaysPanelGenerated::~DisplaysPanelGenerated()
{
	// Disconnect Events
	new_display_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DisplaysPanelGenerated::onNewDisplay ), NULL, this );
	delete_display_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DisplaysPanelGenerated::onDeleteDisplay ), NULL, this );
	manage_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DisplaysPanelGenerated::onManage ), NULL, this );
	
}

NewDisplayDialogGenerated::NewDisplayDialogGenerated( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Display Type") ), wxVERTICAL );
	
	types_ = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT|wxTR_SINGLE );
	sbSizer1->Add( types_, 1, wxALL|wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	sbSizer1->Add( m_staticText2, 0, wxALL, 5 );
	
	type_description_ = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	type_description_->SetMinSize( wxSize( -1,100 ) );
	
	sbSizer1->Add( type_description_, 0, wxALL|wxEXPAND, 5 );
	
	bSizer8->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Display Name") ), wxVERTICAL );
	
	name_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	sbSizer2->Add( name_, 0, wxALL|wxEXPAND, 5 );
	
	bSizer8->Add( sbSizer2, 0, wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	bSizer8->Add( m_sdbSizer1, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer8 );
	this->Layout();
	
	// Connect Events
	types_->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( NewDisplayDialogGenerated::onDisplayDClick ), NULL, this );
	types_->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( NewDisplayDialogGenerated::onDisplaySelected ), NULL, this );
	name_->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( NewDisplayDialogGenerated::onNameEnter ), NULL, this );
	m_sdbSizer1Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewDisplayDialogGenerated::onCancel ), NULL, this );
	m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewDisplayDialogGenerated::onOK ), NULL, this );
}

NewDisplayDialogGenerated::~NewDisplayDialogGenerated()
{
	// Disconnect Events
	types_->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( NewDisplayDialogGenerated::onDisplayDClick ), NULL, this );
	types_->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( NewDisplayDialogGenerated::onDisplaySelected ), NULL, this );
	name_->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( NewDisplayDialogGenerated::onNameEnter ), NULL, this );
	m_sdbSizer1Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewDisplayDialogGenerated::onCancel ), NULL, this );
	m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewDisplayDialogGenerated::onOK ), NULL, this );
	
}

ViewsPanelGenerated::ViewsPanelGenerated( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxArrayString camera_types_Choices;
	camera_types_ = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, camera_types_Choices, 0 );
	camera_types_->SetSelection( 0 );
	camera_types_->SetMinSize( wxSize( 150,-1 ) );
	
	bSizer8->Add( camera_types_, 0, wxALL|wxEXPAND, 5 );
	
	views_list_ = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE ); 
	bSizer8->Add( views_list_, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	save_button_ = new wxButton( this, wxID_ANY, wxT("Save Current"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer9->Add( save_button_, 0, wxALL, 5 );
	
	load_button_ = new wxButton( this, wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer9->Add( load_button_, 0, wxALL, 5 );
	
	delete_button_ = new wxButton( this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer9->Add( delete_button_, 0, wxALL, 5 );
	
	bSizer8->Add( bSizer9, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer8 );
	this->Layout();
	
	// Connect Events
	camera_types_->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ViewsPanelGenerated::onCameraTypeSelected ), NULL, this );
	views_list_->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ViewsPanelGenerated::onViewsClicked ), NULL, this );
	views_list_->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( ViewsPanelGenerated::onViewsDClicked ), NULL, this );
	save_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ViewsPanelGenerated::onSaveClicked ), NULL, this );
	load_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ViewsPanelGenerated::onLoadClicked ), NULL, this );
	delete_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ViewsPanelGenerated::onDeleteClicked ), NULL, this );
}

ViewsPanelGenerated::~ViewsPanelGenerated()
{
	// Disconnect Events
	camera_types_->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ViewsPanelGenerated::onCameraTypeSelected ), NULL, this );
	views_list_->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ViewsPanelGenerated::onViewsClicked ), NULL, this );
	views_list_->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( ViewsPanelGenerated::onViewsDClicked ), NULL, this );
	save_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ViewsPanelGenerated::onSaveClicked ), NULL, this );
	load_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ViewsPanelGenerated::onLoadClicked ), NULL, this );
	delete_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ViewsPanelGenerated::onDeleteClicked ), NULL, this );
	
}

TimePanelGenerated::TimePanelGenerated( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Wall Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer8->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wall_time_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer8->Add( wall_time_, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer7->Add( bSizer8, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer81;
	bSizer81 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Wall Elapsed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer81->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wall_elapsed_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer81->Add( wall_elapsed_, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer7->Add( bSizer81, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer82;
	bSizer82 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("ROS Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer82->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	ros_time_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer82->Add( ros_time_, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer7->Add( bSizer82, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer83;
	bSizer83 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText23 = new wxStaticText( this, wxID_ANY, wxT("ROS Elapsed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	bSizer83->Add( m_staticText23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	ros_elapsed_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer83->Add( ros_elapsed_, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer7->Add( bSizer83, 1, wxEXPAND, 5 );
	
	reset_button_ = new wxButton( this, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	reset_button_->SetToolTip( wxT("Reset Visualization Time (clears all data)") );
	
	bSizer7->Add( reset_button_, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	this->SetSizer( bSizer7 );
	this->Layout();
	
	// Connect Events
	reset_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TimePanelGenerated::onReset ), NULL, this );
}

TimePanelGenerated::~TimePanelGenerated()
{
	// Disconnect Events
	reset_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TimePanelGenerated::onReset ), NULL, this );
	
}

PluginManagerDialogGenerated::PluginManagerDialogGenerated( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Plugins"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	m_staticText9->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer12->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	scrolled_window_ = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	scrolled_window_->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	plugins_sizer_ = new wxBoxSizer( wxVERTICAL );
	
	bSizer17->Add( plugins_sizer_, 1, wxEXPAND, 5 );
	
	scrolled_window_->SetSizer( bSizer17 );
	scrolled_window_->Layout();
	bSizer17->Fit( scrolled_window_ );
	bSizer12->Add( scrolled_window_, 1, wxEXPAND | wxALL, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2->Realize();
	bSizer12->Add( m_sdbSizer2, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer12 );
	this->Layout();
}

PluginManagerDialogGenerated::~PluginManagerDialogGenerated()
{
}

WaitForMasterDialogGenerated::WaitForMasterDialogGenerated( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	text_ = new wxStaticText( this, wxID_ANY, wxT("Could not contact ROS master at [localhost:11311], trying again..."), wxDefaultPosition, wxDefaultSize, 0 );
	text_->Wrap( -1 );
	bSizer15->Add( text_, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	cancel_button_ = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	cancel_button_->SetDefault(); 
	bSizer15->Add( cancel_button_, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer15 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( WaitForMasterDialogGenerated::onClose ) );
	cancel_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WaitForMasterDialogGenerated::onCancel ), NULL, this );
}

WaitForMasterDialogGenerated::~WaitForMasterDialogGenerated()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( WaitForMasterDialogGenerated::onClose ) );
	cancel_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WaitForMasterDialogGenerated::onCancel ), NULL, this );
	
}

ManageDisplaysDialogGenerated::ManageDisplaysDialogGenerated( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	listbox_ = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer16->Add( listbox_, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );
	
	move_down_ = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer17->Add( move_down_, 0, wxALL, 5 );
	
	move_up_ = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer17->Add( move_up_, 0, wxALL, 5 );
	
	remove_ = new wxButton( this, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( remove_, 0, wxALL, 5 );
	
	remove_all_ = new wxButton( this, wxID_ANY, wxT("Remove All"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( remove_all_, 0, wxALL, 5 );
	
	rename_ = new wxButton( this, wxID_ANY, wxT("Rename..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( rename_, 0, wxALL, 5 );
	
	bSizer18->Add( bSizer17, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	ok_ = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( ok_, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	bSizer18->Add( bSizer19, 1, wxEXPAND, 5 );
	
	bSizer16->Add( bSizer18, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer16 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	move_down_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onMoveDown ), NULL, this );
	move_up_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onMoveUp ), NULL, this );
	remove_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onRemove ), NULL, this );
	remove_all_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onRemoveAll ), NULL, this );
	rename_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onRename ), NULL, this );
	ok_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onOK ), NULL, this );
}

ManageDisplaysDialogGenerated::~ManageDisplaysDialogGenerated()
{
	// Disconnect Events
	move_down_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onMoveDown ), NULL, this );
	move_up_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onMoveUp ), NULL, this );
	remove_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onRemove ), NULL, this );
	remove_all_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onRemoveAll ), NULL, this );
	rename_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onRename ), NULL, this );
	ok_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ManageDisplaysDialogGenerated::onOK ), NULL, this );
	
}
