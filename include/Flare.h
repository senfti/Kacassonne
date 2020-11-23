//
// Created by ts on 11.04.20.
//

#ifndef KACASSONNE_FLARE_H
#define KACASSONNE_FLARE_H

#include <wx/dcbuffer.h>
#include "Message.h"
#include "Card.h"

class Flare{
  public:
    double x_ = 0.0;
    double y_ = 0.0;
    int player_ = 0;
    double time_ = 0.0;

    Flare() {}
    Flare(double x, double y, int player) : x_(x), y_(y), player_(player), time_(getTime()) {}
    bool isDraw() const {
      double tmp;
      return std::modf(getTime() - time_, &tmp) < 0.5;
    }
    bool isTimeout() const { return getTime() - time_ > 3; }


    friend void to_json(nlohmann::json& j, const Flare& f) {
      j = nlohmann::json{{"x", f.x_}, {"y", f.y_}, {"player", f.player_}, {"time", f.time_}};
    }
    friend void from_json(const nlohmann::json& j, Flare& f) {
      j.at("x").get_to(f.x_);
      j.at("y").get_to(f.y_);
      j.at("player").get_to(f.player_);
      j.at("time").get_to(f.time_);
    }
};

#endif //KACASSONNE_FLARE_H
