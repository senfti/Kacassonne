//
// Created by ts on 28.03.20.
//

#ifndef CARCASONNE_STONE_H
#define CARCASONNE_STONE_H

#include "Card.h"

void to_json(nlohmann::json& j, const wxColor& c);
void from_json(const nlohmann::json& j, wxColor& c);

class Stone{
  public:
    static constexpr double SIZE = 0.2;

    double x_ = Card::OUTSIDE;
    double y_ = Card::OUTSIDE;
    wxColor color_;

    Stone(wxColor color=wxColor(0, 0, 0)) : color_(color) {}

    void paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale) const;
    void setPosition(double x, double y) { x_ = x; y_ = y; }
    bool isLayed() const { return x_ != Card::OUTSIDE; }
    bool isThere(double x, double y);

    friend void to_json(nlohmann::json& j, const Stone& s) {
      j = nlohmann::json{{"x", s.x_}, {"y", s.y_}, {"color", s.color_}};
    }
    friend void from_json(const nlohmann::json& j, Stone& s) {
      j.at("x").get_to(s.x_);
      j.at("y").get_to(s.y_);
      j.at("color").get_to(s.color_);
    }
};


#endif //CARCASONNE_STONE_H
