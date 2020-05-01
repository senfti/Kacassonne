//
// Created by ts on 24.03.20.
//

#include <MainFrame.h>

#include "main.h"


MainFrame::MainFrame(MyApp* app) : MainFrame_B(nullptr), app_(app), timer_(this){
}

void MainFrame::setGame(Game *game, bool restart){
  {
    std::lock_guard<std::mutex> lock(game->data_lock_);
    game_ = game;
    if(!game_->connection_->iAmHost())
      restart_menu_item_->Enable(false);
    table_panel_->setGame(game);
  }
  std::lock_guard<std::mutex> lock(game_->data_lock_);
  if(restart){
    for(auto& pg : players_guis_)
      pg->setPoints(0);
  }
  else{
    for(const auto &p : game_->players_){
      players_guis_.push_back(new PointGroup(p.name_, p.color_, this));
      info_sizer_->Add(players_guis_.back());
    }
    if(!players_guis_.empty())
      players_guis_[0]->setActive(true, false);
    Connect(timer_.GetId(), wxEVT_TIMER, wxTimerEventHandler(MainFrame::OnTimer), NULL, this);
    timer_.Start(100);
  }
  table_panel_->initOffset();
}

void MainFrame::setCurrentPlayer(int player){
  for(unsigned i = 0; i < players_guis_.size(); i++){
    players_guis_[i]->setActive(player == int(i), game_->current_card_);
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

void MainFrame::restart( wxCommandEvent& event ){
  if(game_->connection_->iAmHost()){
    app_->reset(false);
  }
}

void MainFrame::newGame( wxCommandEvent& event ){
  app_->reset(true);
}

void MainFrame::help( wxCommandEvent& event ){
  HelpDialog_B help_dialog(this);
  help_dialog.ShowModal();
}

void MainFrame::OnTimer(wxTimerEvent &event){
  next_button_->Enable(game_->isActive() && !game_->current_card_ && game_->stack_.getLeftCards());
  back_button_->Enable(game_->isActive());
  shuffle_button_->Enable(game_->isActive() && game_->current_card_ && !game_->played_cards_.empty() && game_->stack_.getLeftCards());
  setCurrentPlayer(game_->current_player_);
  if(game_->update_table_){
    game_->update_table_ = false;
    table_panel_->Refresh();
  }
  int next_preview = game_->getPreviewCard();
  if(next_preview != preview_image_){
    if(next_preview >= 0 && next_preview < int(Card::CARD_IMAGES.size())){
      wxSize size = preview_bitmap_->GetClientSize();
      preview_bitmap_->SetBitmap(wxBitmap(Card::CARD_IMAGES[next_preview].first.Scale(size.x, size.y)));
    }
    else{
      wxSize size = preview_bitmap_->GetClientSize();
      preview_bitmap_->SetBitmap(wxBitmap(wxImage(size)));
    }
    preview_image_ = next_preview;
  }


  for(unsigned i = 0; i < players_guis_.size(); i++){
    std::lock_guard<std::mutex> lock(game_->data_lock_);
    if(players_guis_[i]->getPoints() != game_->players_[i].points_){
      game_->players_[i].points_ = players_guis_[i]->getPoints();
      Message msg;
      msg["type"] = "points";
      msg["idx"] = i;
      msg["points"] = players_guis_[i]->getPoints();
      game_->connection_->send("update", msg);
    }
    players_guis_[i]->setStones(game_->players_[i].getRemainingStones());
  }

  {
    std::lock_guard<std::mutex> lock(game_->data_lock_);
    auto flare = game_->flares_.begin();
    bool refresh = !game_->flares_.empty();
    while(flare != game_->flares_.end()){
      if(flare->isTimeout())
        flare = game_->flares_.erase(flare);
      else
        break;
    }
    if(refresh){
      table_panel_->Refresh();
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

  static unsigned long long last_curr_time = getTime();
  if(game_->current_card_)
    last_curr_time = getTime();
  else if(getTime() - last_curr_time > 3)
    next();
}

void MainFrame::disable(){
  timer_.Stop();
}
