//
// Created by ts on 31.03.20.
//


#include <wx/dcbuffer.h>
#include "GameDialog.h"

GameDialog::GameDialog(Connection *connection)
  : connection_(connection), GameDialog_B(nullptr), timer_(this)
{
  SetTitle(connection->player_name_);
  if(!connection_->iAmHost()){
    start_button_->Disable();
  }
  Connect(timer_.GetId(), wxEVT_TIMER, wxTimerEventHandler(GameDialog::OnTimer), NULL, this);
  timer_.Start(1000);
  receiver_ = new std::thread(&GameDialog::recv, this);
}

GameDialog::~GameDialog(){
  running_ = false;
  receiver_->join();
  delete receiver_;
}

void GameDialog::recv(){
  while(running_){
    auto [t, m] = connection_->recv();
    if(t != ""){
      if(connection_->forMe(m)){
        std::lock_guard<std::mutex> lock(message_lock_);
        pending_messages_.push_back(std::make_pair(t, m));
      }
    }
  }
}

void GameDialog::quit( wxCommandEvent& event ) {
  connection_->send("game_quit", Message());
  EndModal(1);
}

void GameDialog::start( wxCommandEvent& event ) {
  connection_->game_status = int(GameStatus::STARTED);
  ack_.resize(connection_->players_.size(), false);
  ack_[0] = true;
  connection_->send("game_start", Message());
}

void GameDialog::OnTimer(wxTimerEvent& event){
  {
    std::lock_guard<std::mutex> lock(message_lock_);
    for(const auto& [t, m] : pending_messages_){
      if(connection_->iAmHost()){
        if(t == "game_join"){
          connection_->players_.push_back(std::make_pair(m["player_id"].get<int64_t>(), m["player_name"]));
        }
        if(t == "game_quit"){
          int64_t player_id = m["player_id"].get<int64_t>();
          auto player = std::find_if(connection_->players_.begin(), connection_->players_.end(), [player_id](const std::pair<int64_t, std::string>& p) { return p.first == player_id; });
          if(player != connection_->players_.end()){
            connection_->players_.erase(player);
          }
        }
        if(t == "game_start_ack"){
          for(int i=0; i<connection_->players_.size(); i++){
            if(connection_->players_[i].first == m["player_id"].get<int64_t>()){
              ack_[i] = true;
            }
          }
        }
      }
      else{
        if(t == "game_lobby"){
          m["players"].get_to(connection_->players_);
        }
        if(t == "game_start"){
          m["players"].get_to(connection_->players_);
          connection_->send("game_start_ack", Message());
          if(!connection_->iAmHost())
            EndModal(0);
        }
        if(t == "game_quit" && connection_->fromHost(m)){
          wxMessageBox("Host quit!");
          EndModal(1);
        }
      }
    }
    pending_messages_.clear();
  }

  if(connection_->iAmHost()){
    if(connection_->game_status == int(GameStatus::OPEN))
      connection_->send("game_lobby", Message());
    else{
      bool all_ack = true;
      for(auto ack : ack_)
        all_ack = all_ack && ack;
      if(all_ack){
        EndModal(0);
      }
    }
  }

  wxString player_text = "Players in Game " + connection_->game_name_ + ":\n";
  for(const auto& p : connection_->players_){
    player_text += "    " + p.second + "\n";
  }
  players_textctrl_->SetLabel(player_text);
}

