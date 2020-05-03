//
// Created by ts on 24.03.20.
//

#include "PointGroup.h"
#include "MainFrame.h"

PointGroup::PointGroup(const wxString& name, const wxColor& color, wxWindow* parent)
    : wxBoxSizer(wxHORIZONTAL){
  active_panel_ = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(16,16));
  active_panel_->SetBackgroundColour(parent->GetBackgroundColour());
  Add( active_panel_, 0, wxALL, 5 );

  name_field_ = new wxStaticText( parent, wxID_ANY, name, wxDefaultPosition, wxSize(80, -1), 0 );
  name_field_->SetForegroundColour(wxColor(color));
  name_field_->Wrap( -1 );
  Add( name_field_, 0, wxALL, 5 );

  stones_field_ = new wxStaticText( parent, wxID_ANY, "7", wxDefaultPosition, wxSize(10, -1), 0 );
  stones_field_->Wrap( -1 );
  Add( stones_field_, 0, wxALL, 5 );

  point_field_ = new wxTextCtrl( parent, wxID_ANY, "0", wxDefaultPosition, wxSize(50, -1), wxTE_RIGHT);
  Add( point_field_, 0, wxALL, 0 );

  old_points_field_ = new wxStaticText( parent, wxID_ANY, "0", wxDefaultPosition, wxSize(30, -1), 0 );
  Add( old_points_field_, 0, wxALL, 5 );
}

void PointGroup::setActive(bool active, bool card_active){
  active_panel_->SetBackgroundColour(active ? (card_active ? wxColor(0, 255, 0) : wxColor(255, 255, 0)) : this->GetContainingWindow()->GetBackgroundColour() );
  active_panel_->Refresh();
}

void PointGroup::setPoints(int points){
  point_field_->SetValue(std::to_string(points));
}

void PointGroup::setStones(int stones){
  stones_field_->SetLabel(std::to_string(stones));
}

void PointGroup::setOldPoints(int points){
  old_points_field_->SetLabel(std::to_string(points));
}

int PointGroup::getPoints(){
  try{
    points_ = std::atoi(point_field_->GetValue());
  }
  catch(std::exception&){
  }
  return points_;
}

