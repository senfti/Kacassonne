///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
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
	quit_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GameDialog_B::quit ), NULL, this );
	start_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GameDialog_B::start ), NULL, this );
}

GameDialog_B::~GameDialog_B()
{
	// Disconnect Events
	quit_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GameDialog_B::quit ), NULL, this );
	start_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GameDialog_B::start ), NULL, this );

}
