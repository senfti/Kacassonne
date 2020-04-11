//
// Created by ts on 24.03.20.
//

#include "PointGroup.h"
#include "MainFrame.h"

PointGroup::PointGroup(const wxString& name, const wxColor& color, wxWindow* parent)
    : wxBoxSizer(wxHORIZONTAL){
  active_panel_ = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(16,16));
  active_panel_->SetBackgroundColour(parent->GetBackgroundColour());
  Add( active_panel_, 0, wxALL, 1 );

  name_field_ = new wxStaticText( parent, wxID_ANY, name, wxDefaultPosition, wxSize(80, -1), 0 );
  name_field_->SetForegroundColour(wxColor(color));
  name_field_->Wrap( -1 );
  Add( name_field_, 0, wxALL, 5 );

  point_field_ = new wxTextCtrl( parent, wxID_ANY, "0", wxDefaultPosition, wxSize(50, -1), 0);
  Add( point_field_, 0, wxALL, 0 );

  add_point_field_ = new wxTextCtrl( parent, wxID_ANY, "0", wxDefaultPosition, wxSize(30, -1), wxEVT_TEXT_ENTER);
  Add( add_point_field_, 0, wxALL, 0 );

  add_point_field_->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrame::add ), NULL, parent );
}


bool PointGroup::add(int id){
  if(id != add_point_field_->GetId())
    return false;
  try{
    points_ += std::atoi(add_point_field_->GetValue());
    setPoints(points_);
    return true;
  }
  catch(std::exception&){
  }
  return false;
}


void PointGroup::setActive(bool active){
  active_panel_->SetBackgroundColour(active ? wxColor(0, 255, 0) : this->GetContainingWindow()->GetBackgroundColour() );
  active_panel_->Refresh();
}

void PointGroup::setPoints(int points){
  point_field_->SetValue(std::to_string(points));
}

int PointGroup::getPoints(){
  try{
    points_ = std::atoi(point_field_->GetValue());
  }
  catch(std::exception&){
  }
  return points_;
}

