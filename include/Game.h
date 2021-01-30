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
    std::vector<std::vector<int>> points_per_round_;

    std::map<std::string, int> card_count_;
    bool allow_mirror_;

    std::tuple<double, double, double, int, Stone::Type, bool> last_move_stone_ = {0.0, 0.0, 0.0, 0, Stone::Type::STANDARD, false};

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
    bool doMoveStone(double x, double y, int player_number, Stone::Type type=Stone::Type::STANDARD, bool send = true, int restrictions = 0);
    bool moveStone(double x, double y, Stone::Type type, bool any_player=false);
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
    bool validPosition() const;
    bool pointNearLayedCard(double x, double y) const;
    bool cardInHand() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return current_player_ == connection_->player_number_ && current_card_;
    }
    bool isActive() const {
      std::lock_guard<std::mutex> lock(data_lock_);
      return current_player_ == connection_->player_number_;
    }
    bool sendUpdate(const std::string& type, double x=0.0, double y=0.0, int idx=-123, bool flag1 = false, int val1 = 0);
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

    std::vector<std::vector<int>> calcCardStatistics(const std::list<Card>& cards, size_t num_players) const;
    std::tuple<std::vector<wxString>, std::vector<wxString>, std::vector<std::vector<int>>> getCardStatistics(const std::list<Card>& cards) const;
    bool statisticsFair(const std::vector<std::vector<int>>& stats) const;
    void appendPointsPerRound();
    std::vector<std::tuple<wxString, wxColor, std::vector<int>>> getPointsPerRound() const;
};

#endif //CARCASONNE_GAME_H