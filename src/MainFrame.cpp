//
// Created by ts on 24.03.20.
//

#include <MainFrame.h>

#include "MainFrame.h"

MainFrame::MainFrame() : MainFrame_B(nullptr), timer_(this){
}

void MainFrame::setGame(Game *game){
  game_ = game;
  table_panel_->setGame(game);
  info_sizer_->Clear(true);
  for(auto p : players_guis_)
    delete p;
  players_guis_.clear();
  std::lock_guard<std::mutex> lock(game_->data_lock_);
  for(const auto &p : game_->players_){
    players_guis_.push_back(new PointGroup(p.name_, p.color_, this));
    info_sizer_->Add(players_guis_.back());
  }
  if(!players_guis_.empty())
    players_guis_[0]->setActive(true);
  Connect(timer_.GetId(), wxEVT_TIMER, wxTimerEventHandler(MainFrame::OnTimer), NULL, this);
  timer_.Start(100);
}

void MainFrame::setCurrentPlayer(int player){
  for(int i = 0; i < players_guis_.size(); i++){
    players_guis_[i]->setActive(player == i);
  }
}

void MainFrame::quit(wxCommandEvent &event){
  Destroy();
}

void MainFrame::next(wxCommandEvent &event){
  next();
}

void MainFrame::next(){
  if(game_->next()){
    next_button_->Enable(game_->isActive());
    back_button_->Enable(game_->isActive());
    shuffle_button_->Enable(game_->isActive() && game_->current_card_);
    std::lock_guard<std::mutex> lock(game_->data_lock_);
    setCurrentPlayer(game_->current_player_);
  }
}

void MainFrame::back(wxCommandEvent &event){
  if(game_->revert()){
    next_button_->Enable(game_->isActive());
    back_button_->Enable(game_->isActive());
    shuffle_button_->Enable(game_->isActive() && game_->current_card_);
    table_panel_->Refresh();
    table_panel_->Update();
  }
}

void MainFrame::shuffle( wxCommandEvent& event ){
  if(game_->shuffle()){
    table_panel_->Refresh();
    table_panel_->Update();
  }
}

void MainFrame::add(wxCommandEvent &event){
  for(auto pg : players_guis_){
    if(pg->add(event.GetId()))
      break;
  }
}

void MainFrame::OnTimer(wxTimerEvent &event){
  next_button_->Enable(game_->isActive());
  back_button_->Enable(game_->isActive());
  shuffle_button_->Enable(game_->isActive() && game_->current_card_ && !game_->played_cards_.empty());
  setCurrentPlayer(game_->current_player_);
  if(game_->update_table_){
    game_->update_table_ = false;
    table_panel_->Refresh();
  }

  for(int i = 0; i < players_guis_.size(); i++){
    if(players_guis_[i]->getPoints() != game_->players_[i].points_){
      game_->players_[i].points_ = players_guis_[i]->getPoints();
      Message msg;
      msg["type"] = "points";
      msg["idx"] = i;
      msg["points"] = players_guis_[i]->getPoints();
      game_->connection_->send("update", msg);
    }
  }

  std::list<std::pair<std::string, Message>> msgs;
  {
    std::lock_guard<std::mutex> lock(game_->msg_queue_mutex_);
    msgs = game_->msg_queue_;
    game_->msg_queue_.clear();
  }
  for(const auto&[t, m] : msgs){
    if(t == "update" && m["type"] == "points" && m["idx"] < game_->players_.size()){
      game_->players_[m["idx"]].points_ = m["points"];
      players_guis_[m["idx"]]->setPoints(m["points"]);
    }
  }
}
