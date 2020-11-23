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
    std::vector<Flare> count_marks_;
    wxPoint2DDouble last_mouse_pos_ = wxPoint2DDouble(0, 0);
    bool update_old_pts_ = false;

    std::map<std::string, int> card_count_;
    bool allow_mirror_;

    std::tuple<double, double, double, int, bool> last_move_stone_ = {0.0, 0.0, 0.0, 0, false};

    std::mutex msg_queue_mutex_;

    Game(Connection* connection = nullptr, int card_number = 101, const std::map<std::string, int>& card_count = {}, bool allow_mirror_ = true);
    Game(Connection* connection, const Message& reconnect_reply);
    ~Game() {
      running_ = false;
      receiver_->join();
	  delete receiver_;
    }
    bool moveCard(double x, double y, bool force = false);
    bool rotateCard();
    bool flipCard();
    bool layCard(bool force = false);
    bool doMoveStone(double x, double y, int player_number, bool send = true, int restrictions = 0);
    bool moveStone(double x, double y, bool any_player=false);
    bool next();
    bool revert();
    bool shuffle();
    void flare(const wxPoint2DDouble& pos, bool any_player=false);
    void setPoints(int player, int points, bool add, bool send);
    void addMark(double x, double y);
    void removeMark();
    void setMarks(const std::vector<Flare>& marks = std::vector<Flare>());
    void sendMarkMsg();

    int getPreviewCard();
    bool validPosition();
    bool cardInHand() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return current_player_ == connection_->player_number_ && current_card_;
    }
    bool isActive() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return current_player_ == connection_->player_number_;
    }
    bool sendUpdate(const std::string& type, double x=0.0, double y=0.0, int idx=-123, bool flag1 = false);
    int getLeftCards() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return stack_.getLeftCards();
    }
    int getPlayerCount() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return players_.size();
    }
    bool isFirst() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return played_cards_.size() < 2;
    }
    std::vector<Player> getPlayers() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return players_;
    }

    Message getAsMessage() const;
    void updateFromMessage(const Message& msg);

    void recv();
};

#endif //CARCASONNE_GAME_H