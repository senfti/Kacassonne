//
// Created by ts on 09.05.20.
//

#include <ReconnectDialog.h>
#include <wx/wx.h>

ReconnectDialog::ReconnectDialog()
    : ReconnectDialog_B(nullptr){
  try{
    std::ifstream f("last_game.txt");
    if(f.good())
      f >> game_id_ >> player_id_;
  }
  catch(std::exception &e){
    std::cout << e.what() << std::endl;
  }
  game_id_textctrl_->SetValue(std::to_string(game_id_));
  player_id_textctrl_->SetValue(std::to_string(player_id_));
}


void ReconnectDialog::connect( wxCommandEvent& event ){
  try{
    game_id_ = std::atoll(game_id_textctrl_->GetValue());
    player_id_ = std::atoll(player_id_textctrl_->GetValue());
  }
  catch(std::exception&){
    wxMessageBox("Invalid Game ID or Player ID (has to be an integer number)");
    return;
  }
  EndModal(0);
}
