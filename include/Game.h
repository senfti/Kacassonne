//
// Created by ts on 28.03.20.
//

#ifndef CARCASONNE_GAME_H
#define CARCASONNE_GAME_H

#include <thread>
#include "Stack.h"
#include "Stone.h"
#include "Player.h"
#include "Connection.h"
#include "nlohmann/json.hpp"
#include "Flare.h"

class Game{
  public:
    Stack stack_;
    std::list<Card> played_cards_;
    Card* current_card_ = nullptr;
    std::vector<Player> players_;
    int current_player_ = 0;
    Connection* connection_ = nullptr;
    bool update_table_ = true;
    std::thread* receiver_ = nullptr;
    bool running_ = true;
    mutable std::mutex data_lock_;
    std::list<Flare> flares_;
    wxPoint2DDouble last_mouse_pos_ = wxPoint2DDouble(0, 0);

    std::mutex msg_queue_mutex_;
    std::list<std::pair<std::string, Message>> msg_queue_;

    Game(Connection* connection = nullptr, int card_number = 72);
    ~Game() {
      running_ = false;
      receiver_->join();
	  delete receiver_;
    }
    bool moveCard(double x, double y);
    bool rotateCard();
    bool layCard();
    bool doMoveStone(double x, double y, int player_number, bool send = true);
    bool moveStone(double x, double y, bool any_player=false);
    bool next();
    bool revert();
    bool shuffle();
    void flare(const wxPoint2DDouble& pos, bool any_player=false);

    int getPreviewCard();
    bool validPosition();
    bool isActive() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return current_player_ == connection_->player_number_;
    }
    bool sendUpdate(const std::string& type, double x=0.0, double y=0.0, int idx=-123);
    int getLeftCards() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return stack_.getLeftCards();
    }
    int getPlayerCount() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return players_.size();
    }

    Message getAsMessage(bool with_points=false) const;
    void updateFromMessage(const Message& msg);

    void recv();
};

#endif //CARCASONNE_GAME_H