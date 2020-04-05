///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ConnectDialog_B.h"

///////////////////////////////////////////////////////////////////////////

ConnectDialog_B::ConnectDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Server IP"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer1->Add( m_staticText2, 0, wxALL, 5 );

	server_ip_textctrl_ = new wxTextCtrl( this, wxID_ANY, wxT("currynurt.accessio.at"), wxDefaultPosition, wxDefaultSize, 0 );
	server_ip_textctrl_->SetMinSize( wxSize( 160,-1 ) );

	gSizer1->Add( server_ip_textctrl_, 0, wxALL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Server In Port"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer1->Add( m_staticText3, 0, wxALL, 5 );

	pub_port_textctrl_ = new wxTextCtrl( this, wxID_ANY, wxT("10100"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( pub_port_textctrl_, 0, wxALL|wxEXPAND, 5 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Server Out Port"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer1->Add( m_staticText4, 0, wxALL, 5 );

	sub_port_textctrl_ = new wxTextCtrl( this, wxID_ANY, wxT("10200"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( sub_port_textctrl_, 0, wxALL|wxEXPAND, 5 );

	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("My Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gSizer1->Add( m_staticText5, 0, wxALL, 5 );

	name_textctrl_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( name_textctrl_, 0, wxALL|wxEXPAND, 5 );

	ok_button_ = new wxButton( this, wxID_ANY, wxT("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( ok_button_, 0, wxALL, 5 );


	this->SetSizer( gSizer1 );
	this->Layout();
	gSizer1->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	ok_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConnectDialog_B::connect ), NULL, this );
}

ConnectDialog_B::~ConnectDialog_B()
{
	// Disconnect Events
	ok_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConnectDialog_B::connect ), NULL, this );

}
