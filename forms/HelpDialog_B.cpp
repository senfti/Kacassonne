///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Nov 14 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "HelpDialog_B.h"

///////////////////////////////////////////////////////////////////////////

HelpDialog_B::HelpDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Controls:\nRotating Cards: Right Mouse or \"R\" (only if it's your turn)\nMirroring Cards: Hold Right Mouse or \"M\" (only if it's your turn)\nPlacing Cards: Left Mouse (only if it's your turn)\nPlacing Piece: Left Mouse or \"P\"\nRemoving Piece: Left Mouse on Piece or \"P\" when Mouse on piece\nZoom: Mouse wheel\nMove game board: Hold middle mouse or Ctrl while moving mouse\nFlaring: Right mouse or \"F\"\n\nNext: Click \"Next\", press \"Return\" key or wait 3 seconds after placing card\nUndo move: Click \"Back\"\nGet new card (when current card cannot be placed): Click \"Shuffle\"\n\nEnter points: Start typing ([0-9] or '-')"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer5->Add( m_staticText2, 0, wxALL, 5 );


	this->SetSizer( bSizer5 );
	this->Layout();
	bSizer5->Fit( this );

	this->Centre( wxBOTH );
}

HelpDialog_B::~HelpDialog_B()
{
}
