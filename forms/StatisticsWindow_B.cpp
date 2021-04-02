///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Nov 14 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "StatisticsWindow_B.h"

///////////////////////////////////////////////////////////////////////////

StatisticsWindow_B::StatisticsWindow_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	sizer_ = new wxBoxSizer( wxHORIZONTAL );

	graph_panel_ = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL );
	graph_panel_->SetForegroundColour( wxColour( 0, 0, 0 ) );
	graph_panel_->SetBackgroundColour( wxColour( 245, 238, 228 ) );
	graph_panel_->SetMinSize( wxSize( 640,640 ) );

	sizer_->Add( graph_panel_, 0, wxEXPAND | wxALL, 5 );

	stats_grid_ = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	stats_grid_->CreateGrid( 0, 7 );
	stats_grid_->EnableEditing( false );
	stats_grid_->EnableGridLines( true );
	stats_grid_->EnableDragGridSize( false );
	stats_grid_->SetMargins( 0, 0 );

	// Columns
	stats_grid_->AutoSizeColumns();
	stats_grid_->EnableDragColMove( false );
	stats_grid_->EnableDragColSize( false );
	stats_grid_->SetColLabelValue( 0, wxT(" ") );
	stats_grid_->SetColLabelValue( 1, wxT("City") );
	stats_grid_->SetColLabelValue( 2, wxT("Road") );
	stats_grid_->SetColLabelValue( 3, wxT("Meadow") );
	stats_grid_->SetColLabelValue( 4, wxT("Monestary") );
	stats_grid_->SetColLabelValue( 5, wxT("Multi-City") );
	stats_grid_->SetColLabelValue( 6, wxT("Time") );
	stats_grid_->SetColLabelValue( 7, wxEmptyString );
	stats_grid_->SetColLabelValue( 8, wxEmptyString );
	stats_grid_->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	stats_grid_->AutoSizeRows();
	stats_grid_->EnableDragRowSize( false );
	stats_grid_->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance
	stats_grid_->SetLabelFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	// Cell Defaults
	stats_grid_->SetDefaultCellFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	stats_grid_->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_TOP );
	sizer_->Add( stats_grid_, 0, wxALL, 5 );


	this->SetSizer( sizer_ );
	this->Layout();
	sizer_->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	graph_panel_->Connect( wxEVT_PAINT, wxPaintEventHandler( StatisticsWindow_B::paint ), NULL, this );
}

StatisticsWindow_B::~StatisticsWindow_B()
{
	// Disconnect Events
	graph_panel_->Disconnect( wxEVT_PAINT, wxPaintEventHandler( StatisticsWindow_B::paint ), NULL, this );

}
