///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ReconnectDialog_B.h"

///////////////////////////////////////////////////////////////////////////

ReconnectDialog_B::ReconnectDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Game ID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer1->Add( m_staticText3, 0, wxALL, 5 );

	game_id_textctrl_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	game_id_textctrl_->SetMinSize( wxSize( 160,-1 ) );

	gSizer1->Add( game_id_textctrl_, 0, wxALL, 0 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Player ID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer1->Add( m_staticText4, 0, wxALL, 5 );

	player_id_textctrl_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	player_id_textctrl_->SetMinSize( wxSize( 160,-1 ) );

	gSizer1->Add( player_id_textctrl_, 0, wxALL, 0 );

	m_button3 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_button3, 0, wxALL, 5 );

	m_button4 = new wxButton( this, wxID_ANY, wxT("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_button4, 0, wxALL, 5 );


	this->SetSizer( gSizer1 );
	this->Layout();
	gSizer1->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ReconnectDialog_B::cancel ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ReconnectDialog_B::connect ), NULL, this );
}

ReconnectDialog_B::~ReconnectDialog_B()
{
	// Disconnect Events
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ReconnectDialog_B::cancel ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ReconnectDialog_B::connect ), NULL, this );

}
