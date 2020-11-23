///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Nov 14 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "LobbyDialog_B.h"

///////////////////////////////////////////////////////////////////////////

LobbyDialog_B::LobbyDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	window_sizer_ = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );

	version_textctrl_ = new wxStaticText( this, wxID_ANY, wxT("Version: "), wxDefaultPosition, wxDefaultSize, 0 );
	version_textctrl_->Wrap( -1 );
	bSizer41->Add( version_textctrl_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer41->Add( 0, 0, 1, wxEXPAND, 5 );


	window_sizer_->Add( bSizer41, 1, wxEXPAND, 5 );

	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	window_sizer_->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	reconnect_button_ = new wxButton( this, wxID_ANY, wxT("Reconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( reconnect_button_, 0, wxALL, 5 );


	window_sizer_->Add( bSizer5, 1, wxEXPAND, 5 );

	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	window_sizer_->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	load_file_picker_ = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer6->Add( load_file_picker_, 1, wxALL|wxEXPAND, 5 );

	load_button_ = new wxButton( this, wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( load_button_, 0, wxALL, 5 );


	window_sizer_->Add( bSizer6, 1, wxEXPAND, 5 );

	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	window_sizer_->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Game Name"), wxDefaultPosition, wxSize( 80,16 ), wxST_NO_AUTORESIZE );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetMinSize( wxSize( 80,16 ) );

	bSizer4->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	game_name_textctrl_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	game_name_textctrl_->SetMinSize( wxSize( 102,32 ) );

	bSizer4->Add( game_name_textctrl_, 0, wxALL, 5 );

	create_button_ = new wxButton( this, wxID_ANY, wxT("Create"), wxDefaultPosition, wxDefaultSize, 0 );
	create_button_->SetMinSize( wxSize( 80,24 ) );

	bSizer4->Add( create_button_, 0, wxALIGN_CENTER|wxALL, 5 );


	window_sizer_->Add( bSizer4, 0, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	window_sizer_->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	games_sizer_ = new wxBoxSizer( wxVERTICAL );


	window_sizer_->Add( games_sizer_, 1, wxEXPAND, 5 );


	this->SetSizer( window_sizer_ );
	this->Layout();
	window_sizer_->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	reconnect_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LobbyDialog_B::reconnect ), NULL, this );
	load_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LobbyDialog_B::load ), NULL, this );
	create_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LobbyDialog_B::create ), NULL, this );
}

LobbyDialog_B::~LobbyDialog_B()
{
	// Disconnect Events
	reconnect_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LobbyDialog_B::reconnect ), NULL, this );
	load_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LobbyDialog_B::load ), NULL, this );
	create_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LobbyDialog_B::create ), NULL, this );

}
