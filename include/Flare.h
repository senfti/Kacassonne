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
    double x_;
    double y_;
    int player_;
    double time_;

    Flare(double x, double y, int player) : x_(x), y_(y), player_(player), time_(getTime()) {}
    bool isDraw() const {
      double tmp;
      return std::modf(getTime() - time_, &tmp) < 0.5;
    }
    bool isTimeout() const { return getTime() - time_ > 3; }
};

#endif //KACASSONNE_FLARE_H
