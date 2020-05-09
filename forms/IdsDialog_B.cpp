///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "IdsDialog_B.h"

///////////////////////////////////////////////////////////////////////////

IdsDialog_B::IdsDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	ids_text_ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,440 ), wxTE_MULTILINE|wxTE_READONLY );
	bSizer6->Add( ids_text_, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer6 );
	this->Layout();

	this->Centre( wxBOTH );
}

IdsDialog_B::~IdsDialog_B()
{
}
