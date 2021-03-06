//
// Created by ts on 28.03.20.
//

#include <Game.h>
#include <filesystem>

#include "Game.h"


Game::Game(Connection* connection, int card_number, const std::map<std::string, int>& card_count, bool allow_mirror)
  : stack_(card_number, card_count), connection_(connection), card_count_(card_count), allow_mirror_(allow_mirror)
{
  if(connection_->iAmHost()){
    while(!statisticsFair(calcCardStatistics(stack_.getAllCards(), connection_->players_.size()))){
      stack_ = Stack(card_number, card_count);
    }
  }

  if(!std::filesystem::exists("save_games")){
    std::filesystem::create_directory("save_games");
  }
  if(stack_.getLeftCards() < 1)
    return;
  {
    std::lock_guard<std::mutex> lock(data_lock_);
    for(unsigned i = 0; i < connection_->players_.size(); i++){
      players_.push_back(Player(int(connection_->players_[i].color_), connection_->players_[i].name_));
      if(connection_->player_id_ == connection_->players_[i].id_)
        connection_->player_number_ = i;
    }
    if(connection_->iAmHost())
      connection_->send("next", getAsMessage());
    current_card_ = stack_.next();
  }
  moveCard(0, 0, true);
  layCard(true);
  receiver_ = new std::thread(&Game::recv, this);
}

Game::Game(Connection* connection, const Message& reconnect_reply)
  : stack_(-1, {{}}), connection_(connection)
{
  for(unsigned i = 0; i < connection_->players_.size(); i++){
    players_.push_back(Player(int(connection_->players_[i].color_), connection_->players_[i].name_));
    if(connection_->player_id_ == connection_->players_[i].id_)
      connection_->player_number_ = i;
  }
  updateFromMessage(reconnect_reply);
  receiver_ = new std::thread(&Game::recv, this);
}

bool Game::moveCard(double x, double y, bool force){
  std::lock_guard<std::mutex> lock(data_lock_);
  last_mouse_pos_ = wxPoint2DDouble(x, y);
  if((current_player_ == connection_->player_number_ && current_card_) || force){
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
    sendUpdate("rotateCard");
    return true;
  }
  return false;
}

bool Game::flipCard(){
  std::lock_guard<std::mutex> lock(data_lock_);
  if(allow_mirror_ && current_player_ == connection_->player_number_ && current_card_){
    current_card_->flip();
    sendUpdate("flipCard");
    return true;
  }
  return false;
}

bool Game::layCard(bool force){
  std::lock_guard<std::mutex> lock(data_lock_);
  if((current_player_ == connection_->player_number_ && current_card_&& validPosition()) || force){
    current_card_ = nullptr;
    played_cards_.push_back(stack_.get());
    sendUpdate("layCard", played_cards_.back().x(), played_cards_.back().y());
    if(stack_.getLeftCards() == 0)
      appendPointsPerRound();
    return true;
  }
  return false;
}

bool Game::doMoveStone(double x, double y, int player_number, Stone::Type type, bool send, int restrictions){
  last_move_stone_ = {0.0, x, y, player_number, type, false};
  bool one_there = false;
  for(auto &p : players_){
    for(auto &s : p.stones_){
      if(s.isThere(x, y)){
        one_there = true;
        if(restrictions <= 0){
          s.x_ = Card::OUTSIDE;
          s.y_ = Card::OUTSIDE;
          if(send){
            sendUpdate("moveStone", x, y, player_number, false, int(type));
            last_move_stone_ = {getTime(), x, y, player_number, type, false};
          }
          return true;
        }
      }
    }
  }
  if(restrictions >= 0 && !one_there && pointNearLayedCard(x, y)){
    for(auto &s : players_[player_number].stones_){
      if(!s.isLayed() && s.type_ == type){
        s.x_ = x;
        s.y_ = y;
        if(send){
          sendUpdate("moveStone", x, y, player_number, true, int(type));
          last_move_stone_ = {getTime(), x, y, player_number, type, true};
        }
        return true;
      }
    }
  }
  return false;
}

bool Game::moveStone(double x, double y, Stone::Type type, bool any_player){
  bool no_stones;
  {
    std::lock_guard<std::mutex> lock(data_lock_);
    if (any_player || !(current_player_ == connection_->player_number_ && current_card_)) {
      no_stones = !doMoveStone(x, y, connection_->player_number_, type);
    }
  }
  return !no_stones;
}

bool Game::next(){
  {
    std::lock_guard<std::mutex> lock(data_lock_);
    if(current_player_ == connection_->player_number_ && !current_card_ && stack_.getLeftCards() > 0){
      if(move_start_time_ > 0)
        players_[current_player_].move_time_ += getTime() - move_start_time_;
      current_player_ = (current_player_ + 1) % int(players_.size());
      Message msg = getAsMessage();
      connection_->send("next", msg);
      current_card_ = stack_.next();
      if(current_player_ == 0){
        update_old_pts_ = true;
        appendPointsPerRound();
        std::ofstream save_file("save_games/" + std::to_string(connection_->game_id_) + ".json");
        msg["game_status"] = int(GameStatus::STARTED);
        connection_->addStuffToMsg(msg);
        save_file << msg.toJsonString();
      }
      return true;
    }
  }
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

void Game::flare(const wxPoint2DDouble& pos, bool any_player){
  std::lock_guard<std::mutex> lock(data_lock_);
  if (any_player || (current_player_ != connection_->player_number_ || !current_card_)) {
    flares_.emplace_back(Flare(pos.m_x, pos.m_y, connection_->player_number_));
    sendUpdate("flare", pos.m_x, pos.m_y, connection_->player_number_);
  }
}

void Game::setPoints(int player, int points, bool add, bool send){
  std::lock_guard<std::mutex> lock(data_lock_);
  if(player < int(players_.size())){
    players_[player].points_ = (add ? players_[player].points_ + points : points);
    if(send){
      Message msg;
      msg["type"] = "points";
      msg["idx"] = player;
      msg["points"] = players_[player].points_;
      connection_->send("update", msg);
    }
  }
}

void Game::addMark(double x, double y){
  std::lock_guard<std::mutex> lock(data_lock_);
  count_marks_.emplace_back(Flare(x, y, connection_->player_number_));
  sendMarkMsg();
  return;
}

void Game::removeMark(){
  std::lock_guard<std::mutex> lock(data_lock_);
  if(!count_marks_.empty()){
    count_marks_.pop_back();
    sendMarkMsg();
  }
}

void Game::setMarks(const std::vector<Flare>& marks){
  std::lock_guard<std::mutex> lock(data_lock_);
  count_marks_ = marks;
  sendMarkMsg();
}

void Game::sendMarkMsg(){
  Message msg;
  msg["count_marks"] = count_marks_;
  connection_->send("count_marks", msg);
}

int Game::getPreviewCard() {
  std::lock_guard<std::mutex> lock(data_lock_);
  int card_nr = (unsigned(connection_->player_number_) + players_.size() - unsigned(current_player_)) % players_.size();
  card_nr -= (current_card_ ? 0 : 1);
  if (card_nr < 0 || card_nr >= stack_.getLeftCards())
    return -1;
  else if (stack_.next(card_nr))
    return stack_.next(card_nr)->imageNr();
  else
    return -1;
}

Card::Side getSide(const std::array<Card::Side, 4>& sides, int r, bool flipped, int i){
  int tmp = (flipped ? -r-i : r+i) % 4;
  tmp = (tmp < 0 ? tmp+4 : tmp);
  return sides[tmp];
}

bool Game::validPosition() const {
  if(played_cards_.empty())
    return true;

  std::array<Card::Side, 4> curr_sides;
  for(int i=0; i<4; i++){
    curr_sides[i] = getSide(Card::CARD_IMAGES[current_card_->imageNr()].sides_, current_card_->r(), current_card_->flipped(), i);
  }
  static std::array<wxPoint, 4> offsets = {wxPoint(0, -1), wxPoint(-1, 0), wxPoint(0, 1), wxPoint(1, 0)};
  bool has_neighbor = false;
  for(const auto &card : played_cards_){
    if(current_card_->pt() == card.pt())
      return false;

    for(int i=0; i<4; i++){
      if(current_card_->pt() + offsets[i] == card.pt()){
        if(curr_sides[i] != getSide(Card::CARD_IMAGES[card.imageNr()].sides_, card.r(), card.flipped(), i + 2))
          return false;
        has_neighbor = true;
      }
    }
  }
  return has_neighbor;
}

bool Game::pointNearLayedCard(double x, double y) const{
  for(const auto& c : played_cards_){
    if(std::abs(c.x() + 0.5 - x) < 0.8 && std::abs(c.y() + 0.5 - y) < 0.8)
      return true;
  }
  return false;
}

bool Game::sendUpdate(const std::string& type, double x, double y, int idx, bool flag1, int val1){
  Message msg;
  msg["type"] = type;
  msg["x"] = x;
  msg["y"] = y;
  msg["idx"] = idx;
  msg["flag1"] = flag1;
  msg["val1"] = val1;
  connection_->send("update", msg);
  return true;
}

Message Game::getAsMessage() const{
  Message msg;
  msg["stack"] = stack_;
  msg["played_cards"] = played_cards_;
  msg["game_players"] = players_;
  msg["current_player"] = current_player_;
  msg["allow_mirror"] = allow_mirror_;
  return msg;
}

void Game::updateFromMessage(const Message& msg){
  {
    std::lock_guard<std::mutex> lock(data_lock_);
    msg.at("stack").get_to(stack_);
    msg.at("played_cards").get_to(played_cards_);
    msg.at("game_players").get_to(players_);
    msg.at("current_player").get_to(current_player_);
    if(msg.find("allow_mirror") != msg.end())
      msg.at("allow_mirror").get_to(allow_mirror_);
    current_card_ = stack_.next();
  }
  moveCard(last_mouse_pos_.m_x, last_mouse_pos_.m_y);
  update_table_ = true;
}

void Game::recv(){
  wxMilliSleep(1000);
  while(running_){
    try{
      auto[t, m] = connection_->recv();
      if(t == "update" && m["type"] == "points")
        setPoints(m["idx"], m["points"], false, false);
      else if(t == "update"){
        std::lock_guard<std::mutex> lock(data_lock_);
        if(current_card_){
          if(m["type"] == "moveCard")
            current_card_->setPosition(m["x"], m["y"]);
          else if(m["type"] == "rotateCard")
            current_card_->rotate();
          else if(m["type"] == "flipCard")
            current_card_->flip();
          else if(m["type"] == "layCard"){
            current_card_ = nullptr;
            played_cards_.push_back(stack_.get());
            if(stack_.getLeftCards() == 0)
              appendPointsPerRound();
          }
        }
        if(m["type"] == "moveStone" && m["idx"].get<int>() < int(players_.size()))
          doMoveStone(m["x"], m["y"], m["idx"], m["val1"], false, m["flag1"].get<bool>() ? 1 : -1);
        else if(m["type"] == "flare" && m["idx"].get<int>() < int(players_.size())){
          flares_.push_back(Flare(m["x"], m["y"], m["idx"]));
        }
        update_table_ = true;
      }
      else if(t == "next"){
        updateFromMessage(m);
        if(getTime() - std::get<0>(last_move_stone_) < 100.0){
          doMoveStone(std::get<1>(last_move_stone_), std::get<2>(last_move_stone_), std::get<3>(last_move_stone_), std::get<4>(last_move_stone_), true, std::get<5>(last_move_stone_) ? 1 : -1);
        }
        if(current_player_ == 0){
          update_old_pts_ = true;
          if(!played_cards_.empty())
            appendPointsPerRound();
        }
        if(current_player_ == connection_->player_number_)
          move_start_time_ = getTime();
        update_table_ = true;
      }
      else if(t == "reconnect_request"){
        std::lock_guard<std::mutex> lock(data_lock_);
        Message msg = getAsMessage();
        msg["reconnect_player"] = {{"player_id", m["player_id"].get<int64_t>()}, {"player_name", m["player_name"].get<std::string>()}, {"player_number", m["player_number"].get<int64_t>()}};
        connection_->send("reconnect_reply", msg);
      }
      else if(t == "count_marks"){
        std::lock_guard<std::mutex> lock(data_lock_);
        m.at("count_marks").get_to(count_marks_);
        update_table_ = true;
      }
    }
    catch(std::exception& e){
      std::cout << e.what() << std::endl;
    }
  }
}


std::vector<std::vector<int>> Game::calcCardStatistics(const std::list<Card>& cards, size_t num_players) const {
  std::vector<std::vector<int>> content;
  for(size_t pi = 0; pi < num_players; pi++){
    content.emplace_back(std::vector<int>(6, 0));
  }
  size_t i = 0;
  for(const auto& c : cards){
    size_t pi = i % num_players;
    if(c.imageNr() >= int(Card::CARD_IMAGES.size()))
      continue;
    const Card::CardImage& cimg = Card::CARD_IMAGES[c.imageNr()];
    content[pi][0] += std::count(cimg.sides_.begin(), cimg.sides_.end(), Card::Side::CITY);
    content[pi][1] += std::count(cimg.sides_.begin(), cimg.sides_.end(), Card::Side::ROAD);
    content[pi][2] += std::count(cimg.sides_.begin(), cimg.sides_.end(), Card::Side::MEADOW);
    content[pi][3] += cimg.special_ == Card::Special::MONASTERY;
    content[pi][4] += cimg.special_ == Card::Special::EMBLEM || cimg.special_ == Card::Special::MULTI_CITY;
    content[pi][5] += cimg.special_ == Card::Special::CROSSROAD;
    i++;
  }

  return content;
}


std::tuple<std::vector<wxString>, std::vector<wxString>, std::vector<std::vector<int>>> Game::getCardStatistics(const std::list<Card>& cards) const {
  std::lock_guard<std::mutex> lock(data_lock_);
  std::vector<wxString> column_labels = {"City", "Road", "Meadow", "Monastery", "Multi-City", "Time"};
  std::vector<wxString> row_labels;
  for(size_t pi = 0; pi < players_.size(); pi++){
    row_labels.push_back(players_[pi].name_);
  }
  std::vector<std::vector<int>> content = calcCardStatistics(cards, players_.size());
  for(size_t pi = 0; pi < players_.size(); pi++){
    content[pi][5] = players_[pi].move_time_;
  }

  return std::make_tuple(column_labels, row_labels, content);
}


bool Game::statisticsFair(const std::vector<std::vector<int>>& stats) const {
  std::vector<double> sum(stats.front().size(), 0.0);
  for(const auto& ps : stats){
    for(size_t i=0; i<sum.size(); i++){
      sum[i] += ps[i];
    }
  }
  for(const auto& ps : stats){
    for(size_t i=0; i<sum.size(); i++){
      double mean = sum[i] / stats.size();
      if(std::abs(ps[i] - mean) > (2 + std::max(0.1, 0.015*stats.size())*mean)){
        return false;
      }
    }
  }
  return true;
}


void Game::appendPointsPerRound(){
  std::vector<int> curr_pts;
  for(const auto& p : players_)
    curr_pts.push_back(p.points_);
  points_per_round_.push_back(curr_pts);
}


std::vector<std::tuple<wxString, wxColor, std::vector<int>>> Game::getPointsPerRound() const{
  std::lock_guard<std::mutex> lock(data_lock_);
  std::vector<std::tuple<wxString, wxColor, std::vector<int>>> ppr;
  for(size_t pi = 0; pi < players_.size(); pi++){
    ppr.push_back(std::make_tuple(players_[pi].name_, players_[pi].color_, std::vector<int>()));
    for(const auto& r : points_per_round_)
      std::get<2>(ppr[pi]).push_back(r[pi]);
    std::get<2>(ppr[pi]).push_back(players_[pi].points_);
    std::get<2>(ppr[pi]).push_back(players_[pi].points_);
  }
  return ppr;
}
