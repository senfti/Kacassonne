///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PointEntryDialog_B.h"

///////////////////////////////////////////////////////////////////////////

PointEntryDialog_B::PointEntryDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Points:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer8->Add( m_staticText7, 0, wxALL, 10 );

	points_textctrl_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( points_textctrl_, 0, wxALL, 5 );

	add_checkbox_ = new wxCheckBox( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	add_checkbox_->SetValue(true);
	bSizer8->Add( add_checkbox_, 0, wxALL, 7 );


	bSizer7->Add( bSizer8, 1, wxEXPAND, 5 );

	wxArrayString player_choice_Choices;
	player_choice_ = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, player_choice_Choices, 0 );
	player_choice_->SetSelection( 0 );
	bSizer7->Add( player_choice_, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_button2 = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button2, 0, wxALL, 5 );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button3 = new wxButton( this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );

	m_button3->SetDefault();
	bSizer3->Add( m_button3, 0, wxALL, 5 );


	bSizer7->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer7 );
	this->Layout();
	bSizer7->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ) );
	m_staticText7->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
	points_textctrl_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
	add_checkbox_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
	player_choice_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PointEntryDialog_B::cancel ), NULL, this );
	m_button2->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PointEntryDialog_B::ok ), NULL, this );
	m_button3->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
}

PointEntryDialog_B::~PointEntryDialog_B()
{
	// Disconnect Events
	this->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ) );
	m_staticText7->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
	points_textctrl_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
	add_checkbox_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
	player_choice_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PointEntryDialog_B::cancel ), NULL, this );
	m_button2->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PointEntryDialog_B::ok ), NULL, this );
	m_button3->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( PointEntryDialog_B::keyDown ), NULL, this );

}
