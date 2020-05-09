//
// Created by ts on 03.04.20.
//

#include "LobbyDialog.h"
#include "ReconnectDialog.h"

LobbyDialog::LobbyDialog(Connection* connection)
    : LobbyDialog_B(nullptr), connection_(connection), timer_(this){
  version_textctrl_->SetLabel(wxString("VERSION: ") + VERSION);
  Connect(timer_.GetId(), wxEVT_TIMER, wxTimerEventHandler(LobbyDialog::OnTimer), NULL, this);
  timer_.Start(1000);
  receiver_ = new std::thread(&LobbyDialog::recv, this);
}

LobbyDialog::~LobbyDialog(){
	if (running_){
    running_ = false;
    receiver_->join();
  }
	delete receiver_;
}


void LobbyDialog::recv(){
  while(running_){
    if(during_reconnect_){
      wxMilliSleep(100);
      continue;
    }
    auto [t, m] = connection_->recv();
    if(t == "game_lobby" && connection_->forMe(m)){
      std::lock_guard<std::mutex> lock(message_lock_);
      pending_messages_.push_back(std::make_pair(t, m));
    }
  }
}

void LobbyDialog::create( wxCommandEvent& event ){
  connection_->game_name_ = game_name_textctrl_->GetValue();
  connection_->game_id_ = getID();
  connection_->host_ = connection_->player_id_;
  connection_->players_ = {PlayerCon(connection_->player_id_, connection_->player_name_, 0)};
  running_ = false;
  receiver_->join();
  EndModal(0);
}

void LobbyDialog::reconnect( wxCommandEvent& event ){
  during_reconnect_ = true;
  int64_t old_pid = connection_->player_id_;
  ReconnectDialog* rd = new ReconnectDialog();
  if(rd->ShowModal() != 0){
    connection_->subscribeToLobby();
    delete rd;
    return;
  }

  connection_->game_id_ = rd->game_id_;
  connection_->player_id_ = rd->player_id_;
  delete rd;

  connection_->subscribeToGame();
  connection_->send("reconnect_request", Message());
  double start = getTime();
  while(getTime() - start < 5.0){
    auto [t, m] = connection_->recv();
    if(t == "reconnect_reply"){
      GameToJoin game(m["game_name"], m["game_id"], m["host"], m["players"], this);
      connection_->game_name_ = game.name_;
      connection_->game_id_ = game.id_;
      connection_->host_ = game.host_;
      connection_->players_ = game.players_;
      reconnect_reply_ = m;
      EndModal(0);
      running_ = false;
      receiver_->join();
      return;
    }
  }
  wxMessageBox("Reconnect failed: Timeout");
  connection_->player_id_ = old_pid;
  connection_->subscribeToLobby();
  during_reconnect_ = false;
}

void LobbyDialog::join( wxCommandEvent& event ){
  for(const auto& game : games_){
    if(game.isButtonID(event.GetId())){
      connection_->game_name_ = game.name_;
      connection_->game_id_ = game.id_;
      connection_->host_ = game.host_;
      connection_->players_ = game.players_;
      running_ = false;
      receiver_->join();
      connection_->send("game_join", Message());
      EndModal(0);
      return;
    }
  }
  wxMessageBox("Game not found: This should never happen!");
}

void LobbyDialog::OnTimer(wxTimerEvent &event){
  std::lock_guard<std::mutex> lock(message_lock_);
  for(const auto& [t, m] : pending_messages_){
    if(m["game_status"].get<int>() == int(GameStatus::OPEN)){
      int64_t game_id = m["game_id"].get<int64_t>();
      if(std::find_if(games_.begin(), games_.end(), [game_id] (const GameToJoin& game) { return game.id_ == game_id; }) == games_.end()){
        games_.emplace_back(m["game_name"], m["game_id"], m["host"], m["players"], this);
        games_.back().button_->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LobbyDialog::join), NULL, this);
        games_sizer_->Add(games_.back().button_, 0, wxALL|wxEXPAND, 5);
        window_sizer_->Layout();
        this->Fit();
        this->Layout();
      }
    }
    else{
      int64_t game_id = m["game_id"].get<int64_t>();
      auto game = std::find_if(games_.begin(), games_.end(), [game_id] (const GameToJoin& game) { return game.id_ == game_id; });
      if(game != games_.end()){
        game->button_->Disable();
      }
    }
  }
}
