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
    static std::vector<wxImage> STONE_IMAGES;
    static bool initStoneImages();

    double x_ = Card::OUTSIDE;
    double y_ = Card::OUTSIDE;
    wxColor color_;
    int player_ = 0;

    Stone(wxColor color=wxColor(0, 0, 0), int player=0) : color_(color), player_(player) { initStoneImages(); }

    void paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale) const;
    void setPosition(double x, double y) { x_ = x; y_ = y; }
    bool isLayed() const { return x_ != Card::OUTSIDE; }
    bool isThere(double x, double y);

    friend void to_json(nlohmann::json& j, const Stone& s) {
      j = nlohmann::json{{"x", s.x_}, {"y", s.y_}, {"color", s.color_}, {"player", s.player_}};
    }
    friend void from_json(const nlohmann::json& j, Stone& s) {
      j.at("x").get_to(s.x_);
      j.at("y").get_to(s.y_);
      j.at("color").get_to(s.color_);
      j.at("player").get_to(s.player_);
    }
};


#endif //CARCASONNE_STONE_H
