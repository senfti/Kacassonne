///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Nov 14 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GameDialog_B.h"

///////////////////////////////////////////////////////////////////////////

GameDialog_B::GameDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,11 ), wxDefaultSize );

	sizer_ = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Number of Cards:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALL, 5 );

	numcard_textctrl_ = new wxTextCtrl( this, wxID_ANY, wxT("101"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_RIGHT );
	bSizer3->Add( numcard_textctrl_, 0, wxALL, 0 );

	mirror_checkbox_ = new wxCheckBox( this, wxID_ANY, wxT("Allow Mirror"), wxDefaultPosition, wxDefaultSize, 0 );
	mirror_checkbox_->SetValue(true);
	bSizer3->Add( mirror_checkbox_, 0, wxALL, 2 );

	settings_button_ = new wxButton( this, wxID_ANY, wxT("Settings"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( settings_button_, 0, wxALL, 0 );


	sizer_->Add( bSizer3, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer4->Add( m_staticText3, 0, wxALL, 5 );

	wxString color_choice_Choices[] = { wxT("Red"), wxT("Blue"), wxT("Yellow"), wxT("Black"), wxT("White"), wxT("Green"), wxT("Purple"), wxT("Teal"), wxT("Orange"), wxT("Pink"), wxT("Green2"), wxT("Gray"), wxT("Random") };
	int color_choice_NChoices = sizeof( color_choice_Choices ) / sizeof( wxString );
	color_choice_ = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, color_choice_NChoices, color_choice_Choices, 0 );
	color_choice_->SetSelection( 0 );
	bSizer4->Add( color_choice_, 0, wxALL, 0 );


	sizer_->Add( bSizer4, 1, wxEXPAND, 5 );

	players_textctrl_ = new wxStaticText( this, wxID_ANY, wxT("Players in Game: \n"), wxDefaultPosition, wxSize( 320,480 ), 0 );
	players_textctrl_->Wrap( -1 );
	players_textctrl_->SetFont( wxFont( 16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	players_textctrl_->SetMinSize( wxSize( 320,480 ) );

	sizer_->Add( players_textctrl_, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	quit_button_ = new wxButton( this, wxID_ANY, wxT("Quit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( quit_button_, 0, wxALL, 5 );


	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );

	start_button_ = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( start_button_, 0, wxALL, 5 );


	sizer_->Add( bSizer2, 0, wxEXPAND, 5 );


	this->SetSizer( sizer_ );
	this->Layout();
	sizer_->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	settings_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GameDialog_B::changeSettings ), NULL, this );
	color_choice_->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GameDialog_B::changeColor ), NULL, this );
	quit_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GameDialog_B::quit ), NULL, this );
	start_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GameDialog_B::start ), NULL, this );
}

GameDialog_B::~GameDialog_B()
{
	// Disconnect Events
	settings_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GameDialog_B::changeSettings ), NULL, this );
	color_choice_->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GameDialog_B::changeColor ), NULL, this );
	quit_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GameDialog_B::quit ), NULL, this );
	start_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GameDialog_B::start ), NULL, this );

}
