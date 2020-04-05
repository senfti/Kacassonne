///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "HostDialog_B.h"

///////////////////////////////////////////////////////////////////////////

HostDialog_B::HostDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* player_sizer_;
	player_sizer_ = new wxBoxSizer( wxVERTICAL );

	self_text_ = new wxStaticText( this, wxID_ANY, wxT("Me: "), wxDefaultPosition, wxDefaultSize, 0 );
	self_text_->Wrap( -1 );
	player_sizer_->Add( self_text_, 0, wxALL, 5 );


	bSizer1->Add( player_sizer_, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	cancel_button_ = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( cancel_button_, 0, wxALL, 5 );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	start_button_ = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( start_button_, 0, wxALL, 5 );


	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	cancel_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HostDialog_B::cancel ), NULL, this );
	start_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HostDialog_B::start ), NULL, this );
}

HostDialog_B::~HostDialog_B()
{
	// Disconnect Events
	cancel_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HostDialog_B::cancel ), NULL, this );
	start_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HostDialog_B::start ), NULL, this );

}
