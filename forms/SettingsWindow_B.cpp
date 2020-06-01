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

	flip_checkbox_ = new wxCheckBox( this, wxID_ANY, wxT("Card Flipping"), wxDefaultPosition, wxDefaultSize, 0 );
	flip_checkbox_->SetValue(true);
	bSizer7->Add( flip_checkbox_, 0, wxALL, 5 );

	m_scrolledWindow2 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow2->SetScrollRate( 5, 5 );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 4, 0, 0 );


	m_scrolledWindow2->SetSizer( gSizer1 );
	m_scrolledWindow2->Layout();
	gSizer1->Fit( m_scrolledWindow2 );
	bSizer7->Add( m_scrolledWindow2, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer7 );
	this->Layout();
	bSizer7->Fit( this );

	this->Centre( wxBOTH );
}

SettingsWindow_B::~SettingsWindow_B()
{
}
