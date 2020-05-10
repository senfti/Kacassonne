//
// Created by ts on 10.05.20.
//

#include "PointEntryDialog.h"


PointEntryDialog::PointEntryDialog(wxWindow* parent, int digit, const std::vector<Player>& players, int myself)
    : PointEntryDialog_B(parent)
{
  points_textctrl_->SetValue(digit >= 0 ? std::to_string(digit) : "-");
  for(const auto& p : players)
    player_choice_->Append(p.name_);
  player_choice_->SetSelection(myself);
  points_textctrl_->SetFocus();
  points_textctrl_->SetSelection(0, 0);
  points_textctrl_->SetInsertionPoint(1);
}


void PointEntryDialog::keyDown( wxKeyEvent& event ){
  if(event.GetKeyCode() == WXK_RETURN){
    try{
      points_ = std::atoi(points_textctrl_->GetValue());
      EndModal(0);
    }
    catch(std::exception&){
      points_textctrl_->SetValue("");
      points_textctrl_->SetFocus();
    }
  }
  else if(event.GetKeyCode() == WXK_ESCAPE)
    EndModal(-1);
  else if(event.GetKeyCode() == WXK_UP || event.GetKeyCode() == WXK_LEFT){
    if(player_choice_->GetSelection() > 0)
      player_choice_->SetSelection(player_choice_->GetSelection() - 1);
  }
  else if(event.GetKeyCode() == WXK_DOWN || event.GetKeyCode() == WXK_RIGHT){
    if(player_choice_->GetSelection() < int(player_choice_->GetStrings().size()) - 1)
      player_choice_->SetSelection(player_choice_->GetSelection() + 1);
  }
  else{
    event.Skip();
  }
}
