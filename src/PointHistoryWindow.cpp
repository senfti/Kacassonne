//
// Created by ts on 31.05.20.
//

#include "PointHistoryWindow.h"

PointHistoryWindow::PointHistoryWindow( wxWindow* parent, const std::vector<Player>& players, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
    : wxFrame( parent, id, title, pos, wxSize(80*players.size()+40, 640), style), point_count_(players.size(), 0), last_points_(players.size(), 0)
{
  this->SetSizeHints( wxDefaultSize, wxDefaultSize );

  wxBoxSizer* bSizer2;
  bSizer2 = new wxBoxSizer( wxVERTICAL );

  hide_button_ = new wxButton( this, wxID_ANY, wxT("Hide"), wxDefaultPosition, wxDefaultSize, 0 );
  hide_button_->SetMinSize( wxSize( 80,24 ) );

  bSizer2->Add( hide_button_, 0, wxALIGN_CENTER|wxALL, 5 );

  pts_grid_ = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

  // Grid
  pts_grid_->CreateGrid( 100, players.size() );
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
  for(size_t i=0; i<players.size(); i++)
    pts_grid_->SetColLabelValue(i, players[i].name_);

  // Rows
  pts_grid_->AutoSizeRows();
  pts_grid_->EnableDragRowSize( false );
  pts_grid_->SetRowLabelSize( 0 );
  pts_grid_->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

  // Label Appearance
  pts_grid_->SetLabelFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

  // Cell Defaults
  pts_grid_->SetDefaultCellFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
  pts_grid_->SetDefaultCellAlignment( wxALIGN_CENTER, wxALIGN_CENTER );
  bSizer2->Add( pts_grid_, 0, wxALL|wxEXPAND, 0 );


  this->SetSizer( bSizer2 );
  this->Layout();

  this->Centre( wxBOTH );

  hide_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PointHistoryWindow::hide ), NULL, this );
}

PointHistoryWindow::~PointHistoryWindow()
{
  hide_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PointHistoryWindow::hide ), NULL, this );
}


void PointHistoryWindow::setPoints(int player, int points){
  if(last_points_[player] != points){
    pts_grid_->SetCellValue(point_count_[player], player, std::to_string(points) + " (" + std::to_string(++pt_number_) + ")");
    point_count_[player]++;
    last_points_[player] = points;
  }
}
