//
// Created by ts on 29.03.20.
//

#ifndef CARCASONNE_PLAYER_H
#define CARCASONNE_PLAYER_H


#include "Stone.h"

class Player{
  public:
    std::list<Stone> stones_;
    wxString name_;
    wxColor color_;
    int points_ = 0;
    double move_time_ = 0.0;

    Player(int number = -1, const wxString& name = "");

    int getRemainingStones(Stone::Type type = Stone::Type::STANDARD) const;

    friend void to_json(nlohmann::json& j, const Player& p) {
      j = nlohmann::json{{"stones", p.stones_}, {"color", p.color_}, {"name", p.name_}, {"points", p.points_}, {"move_time", p.move_time_}};
    }
    friend void from_json(const nlohmann::json& j, Player& p) {
      j.at("stones").get_to(p.stones_);
      j.at("color").get_to(p.color_);
      p.name_ = j.at("name").get<std::string>();
      j.at("points").get_to(p.points_);
      j.at("move_time").get_to(p.move_time_);
    }
};

#endif //CARCASONNE_PLAYER_H
