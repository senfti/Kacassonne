//
// Created by ts on 31.03.20.
//


#include <wx/dcbuffer.h>
#include "GameDialog.h"
#include <wx/valnum.h>
#include <random>

GameDialog::GameDialog(Connection *connection)
  : GameDialog_B(nullptr), connection_(connection), timer_(this)
{
  wxIntegerValidator<unsigned long> val(&card_number_);
  val.SetMin(1);
  val.SetMax(999);
  numcard_textctrl_->SetValidator(val);
  SetTitle(connection->player_name_);
  if(!connection_->iAmHost()){
    start_button_->Disable();
    numcard_textctrl_->Disable();
  }
  Connect(timer_.GetId(), wxEVT_TIMER, wxTimerEventHandler(GameDialog::OnTimer), NULL, this);
  timer_.Start(200);
  receiver_ = new std::thread(&GameDialog::recv, this);
}

GameDialog::~GameDialog(){
  if(running_){
    running_ = false;
    receiver_->join();
  }
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

void GameDialog::changeColor( wxCommandEvent& event ){
  if(running_){
    if(connection_->iAmHost()){
      connection_->players_[0].color_ = size_t(color_choice_->GetSelection());
    }
    else{
      size_t color = size_t(color_choice_->GetSelection());
      Message msg;
      msg["new_color"] = color;
      connection_->send("change_color", msg);
    }
  }
}

void GameDialog::quit( wxCommandEvent& event ) {
  connection_->send("game_quit", Message());
  EndModal(1);
}

void GameDialog::start( wxCommandEvent& event ) {
  std::mt19937 eng(time(0));
  std::shuffle(connection_->players_.begin(), connection_->players_.end(), eng);
  connection_->game_status_ = int(GameStatus::STARTED);
  ack_.resize(connection_->players_.size(), false);
  for(unsigned i=0; i<connection_->players_.size(); i++){
    if(connection_->players_[i].id_ == connection_->player_id_)
      ack_[i] = true;
  }
  connection_->send("game_start", Message());
  card_number_ = std::atoi((const char*)(numcard_textctrl_->GetValue()));
}

void GameDialog::OnTimer(wxTimerEvent& event){
  {
    std::lock_guard<std::mutex> lock(message_lock_);
    for(const auto& [t, m] : pending_messages_){
      if(connection_->iAmHost()){
        if(t == "change_color"){
          int64_t player_id = m["player_id"].get<int64_t>();
          auto player = std::find_if(connection_->players_.begin(), connection_->players_.end(), [player_id](const PlayerCon& p) { return p.id_ == player_id; });
          if(player != connection_->players_.end()){
            player->color_ = m["new_color"].get<size_t>();
          }
        }
        if(t == "game_join"){
          connection_->players_.push_back(PlayerCon(m["player_id"].get<int64_t>(), m["player_name"], connection_->players_.size()));
        }
        if(t == "game_quit"){
          int64_t player_id = m["player_id"].get<int64_t>();
          auto player = std::find_if(connection_->players_.begin(), connection_->players_.end(), [player_id](const PlayerCon& p) { return p.id_ == player_id; });
          if(player != connection_->players_.end()){
            connection_->players_.erase(player);
          }
        }
        if(t == "game_start_ack"){
          for(unsigned i=0; i<connection_->players_.size(); i++){
            if(connection_->players_[i].id_ == m["player_id"].get<int64_t>()){
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
          connection_->game_status_ = int(GameStatus::STARTED);
          connection_->send("game_start_ack", Message());
          if(!connection_->iAmHost()){
            running_ = false;
            receiver_->join();
            EndModal(0);
          }
        }
        if(t == "game_quit" && connection_->fromHost(m)){
          running_ = false;
          wxMessageBox("Host quit!");
          receiver_->join();
          EndModal(1);
        }
      }
    }
    pending_messages_.clear();
  }

  if(connection_->iAmHost()){
    if(connection_->game_status_ == int(GameStatus::OPEN))
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
    player_text += "    " + p.name_ + ": " + color_choice_->GetString(p.color_) + "\n";
  }
  players_textctrl_->SetLabel(player_text);
}

