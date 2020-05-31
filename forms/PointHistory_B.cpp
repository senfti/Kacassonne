///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PointHistory_B.h"

///////////////////////////////////////////////////////////////////////////

PointHistoryWindow::PointHistoryWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	pts_grid_ = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	pts_grid_->CreateGrid( 100, 5 );
	pts_grid_->EnableEditing( false );
	pts_grid_->EnableGridLines( true );
	pts_grid_->EnableDragGridSize( false );
	pts_grid_->SetMargins( 0, 0 );

	// Columns
	pts_grid_->SetColSize( 0, 80 );
	pts_grid_->EnableDragColMove( false );
	pts_grid_->EnableDragColSize( false );
	pts_grid_->SetColLabelSize( 30 );
	pts_grid_->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	pts_grid_->AutoSizeRows();
	pts_grid_->EnableDragRowSize( false );
	pts_grid_->SetRowLabelSize( 0 );
	pts_grid_->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance
	pts_grid_->SetLabelFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	// Cell Defaults
	pts_grid_->SetDefaultCellFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	pts_grid_->SetDefaultCellAlignment( wxALIGN_CENTER, wxALIGN_TOP );
	bSizer2->Add( pts_grid_, 0, wxALL|wxEXPAND, 0 );


	this->SetSizer( bSizer2 );
	this->Layout();

	this->Centre( wxBOTH );
}

PointHistoryWindow::~PointHistoryWindow()
{
}
