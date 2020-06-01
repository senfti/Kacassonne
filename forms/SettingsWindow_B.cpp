///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SettingsWindow_B.h"

///////////////////////////////////////////////////////////////////////////

SettingsWindow_B::SettingsWindow_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Card Count Setting:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALL, 5 );

	wxArrayString setting_choice_Choices;
	setting_choice_ = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, setting_choice_Choices, 0 );
	setting_choice_->SetSelection( 0 );
	bSizer3->Add( setting_choice_, 0, wxALL, 0 );


	bSizer7->Add( bSizer3, 0, wxEXPAND, 5 );

	image_sizer_ = new wxGridSizer( 0, 10, 0, 0 );


	bSizer7->Add( image_sizer_, 1, 0, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALL, 5 );

	name_textctrl_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), 0 );
	bSizer2->Add( name_textctrl_, 0, wxALL, 0 );

	save_button_ = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( save_button_, 0, wxALL, 0 );


	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );

	ok_button_ = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( ok_button_, 0, wxALL, 0 );


	bSizer7->Add( bSizer2, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer7 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	setting_choice_->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SettingsWindow_B::changeSetting ), NULL, this );
	save_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsWindow_B::save ), NULL, this );
	ok_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsWindow_B::ok ), NULL, this );
}

SettingsWindow_B::~SettingsWindow_B()
{
	// Disconnect Events
	setting_choice_->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SettingsWindow_B::changeSetting ), NULL, this );
	save_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsWindow_B::save ), NULL, this );
	ok_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsWindow_B::ok ), NULL, this );

}
