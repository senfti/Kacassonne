//
// Created by ts on 28.03.20.
//

#include <Game.h>

#include "Game.h"


Game::Game(Connection* connection)
  : connection_(connection)
{
  std::lock_guard<std::mutex> lock(data_lock_);
  for(int i=0; i<connection_->players_.size(); i++){
    players_.push_back(Player(i, connection_->players_[i].second));
    if(connection_->player_id_ == connection_->players_[i].first)
      connection_->player_number_ = i;
  }
  if(connection_->iAmHost()){
    connection_->send("next", getAsMessage());
  }
  current_card_ = stack_.next();
  receiver_ = new std::thread(&Game::recv, this);
}

bool Game::moveCard(double x, double y){
  std::lock_guard<std::mutex> lock(data_lock_);
  if(current_player_ == connection_->player_number_ && current_card_){
    x = std::floor(x);
    y = std::floor(y);
    if(x != current_card_->x() || y != current_card_->y()){
      current_card_->setPosition(x, y);
      sendUpdate("moveCard", x, y);
      return true;
    }
  }
  return false;
}

bool Game::rotateCard(){
  std::lock_guard<std::mutex> lock(data_lock_);
  if(current_player_ == connection_->player_number_ && current_card_){
    current_card_->rotate();
    sendUpdate("rotateCard", current_card_->r());
    return true;
  }
  return false;
}

bool Game::layCard(){
  std::lock_guard<std::mutex> lock(data_lock_);
  if(current_player_ == connection_->player_number_ && current_card_ && current_card_&& validPosition()){
    current_card_ = nullptr;
    played_cards_.push_back(stack_.get());
    sendUpdate("layCard", played_cards_.back().x(), played_cards_.back().y());
    return true;
  }
  return false;
}

bool Game::doMoveStone(double x, double y, int player_number, bool send){
  for(auto &p : players_){
    for(auto &s : p.stones_){
      if(s.isThere(x, y)){
        s.x_ = Card::OUTSIDE;
        s.y_ = Card::OUTSIDE;
        if(send)
          sendUpdate("moveStone", x, y, player_number);
        return true;
      }
    }
  }
  for(auto &s : players_[player_number].stones_){
    if(s.x_ == Card::OUTSIDE){
      s.x_ = x;
      s.y_ = y;
      if(send)
        sendUpdate("moveStone", x, y, player_number);
      return true;
    }
  }
  return false;
}

bool Game::moveStone(double x, double y){
  bool no_stones;
  {
    std::lock_guard<std::mutex> lock(data_lock_);
    if(!(current_player_ == connection_->player_number_ && current_card_)){
      no_stones = !doMoveStone(x, y, connection_->player_number_);
    }
  }
  if(no_stones)
    wxMessageBox("No Stones!");
  return !no_stones;
}

bool Game::next(){
  {
    std::lock_guard<std::mutex> lock(data_lock_);
    if(current_player_ == connection_->player_number_ && !current_card_){
      current_player_ = (current_player_ + 1) % int(players_.size());
      connection_->send("next", getAsMessage());
      current_card_ = stack_.next();
      return true;
    }
  }
  if(!current_card_)
    wxMessageBox("Game Finished!");
  return false;
}

bool Game::revert(){
  std::lock_guard<std::mutex> lock(data_lock_);
  if(current_player_ == connection_->player_number_){
    played_cards_.back().setPosition(Card::OUTSIDE, Card::OUTSIDE);
    stack_.push(played_cards_.back());
    played_cards_.pop_back();
    if(current_card_ != nullptr)
      current_player_ = (current_player_ + int(players_.size()) - 1) % int(players_.size());
    current_card_ = stack_.next();
    connection_->send("next", getAsMessage());
    return true;
  }
  return false;
}

bool Game::shuffle(){
  {
    std::lock_guard<std::mutex> lock(data_lock_);
    if(current_player_ == connection_->player_number_ && current_card_){
      stack_.shuffle();
      connection_->send("next", getAsMessage());
      current_card_ = stack_.next();
      return true;
    }
  }
  return false;
}

bool Game::validPosition(){
  bool has_neighbor = false;
  for(const auto &card : played_cards_){
    if(current_card_->x() == card.x() && current_card_->y() == card.y())
      return false;
    if((current_card_->x() == card.x() && std::abs(current_card_->y() - card.y()) == 1) ||
       (current_card_->y() == card.y() && std::abs(current_card_->x() - card.x()) == 1))
      has_neighbor = true;
  }
  return has_neighbor || played_cards_.empty();
}

bool Game::sendUpdate(const std::string& type, double x, double y, int idx){
  Message msg;
  msg["type"] = type;
  msg["x"] = x;
  msg["y"] = y;
  msg["idx"] = idx;
  connection_->send("update", msg);
}

Message Game::getAsMessage() const{
  Message msg;
  msg["stack"] = stack_;
  msg["played_cards"] = played_cards_;
  msg["game_players"] = players_;
  msg["current_player"] = current_player_;
  return msg;
}

void Game::updateFromMessage(const Message& msg){
  {
    std::lock_guard<std::mutex> lock(data_lock_);
    msg.at("stack").get_to(stack_);
    msg.at("played_cards").get_to(played_cards_);
    msg.at("game_players").get_to(players_);
    msg.at("current_player").get_to(current_player_);
    current_card_ = stack_.next();
  }
}

void Game::recv(){
  wxMilliSleep(1000);
  while(running_){
    try{
      auto[t, m] = connection_->recv();
      if(t == "update" && m["type"] == "points"){
        std::lock_guard<std::mutex> lock(msg_queue_mutex_);
        msg_queue_.push_back(std::make_pair(t, m));
      } else if(t == "update"){
        std::lock_guard<std::mutex> lock(data_lock_);
        if(current_card_){
          if(m["type"] == "moveCard")
            current_card_->setPosition(m["x"], m["y"]);
          if(m["type"] == "rotateCard")
            current_card_->rotate(m["x"].get<double>());
          if(m["type"] == "layCard"){
            current_card_ = nullptr;
            played_cards_.push_back(stack_.get());
          }
        }
        if(m["type"] == "moveStone" && m["idx"].get<int>() < players_.size())
          doMoveStone(m["x"], m["y"], m["idx"], false);
        update_table_ = true;
      } else if(t == "next"){
        updateFromMessage(m);
        update_table_ = true;
      }
    }
    catch(std::exception& e){
      std::cout << e.what() << std::endl;
    }
  }
}