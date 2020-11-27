//
// Created by ts on 28.03.20.
//

#ifndef CARCASONNE_STONE_H
#define CARCASONNE_STONE_H

#include "Card.h"

void to_json(nlohmann::json& j, const wxColor& c);
void from_json(const nlohmann::json& j, wxColor& c);
void to_json(nlohmann::json& j, const wxImage::HSVValue& c);
void from_json(const nlohmann::json& j, wxImage::HSVValue& c);

class Stone{
  public:
    static constexpr double SIZE = 0.2;
    static std::vector<wxImage> STONE_IMAGES;
    static bool initStoneImages();
    enum class Type{STANDARD = 0, HORSE = 1, ANY = 128};

    double x_ = Card::OUTSIDE;
    double y_ = Card::OUTSIDE;
    wxImage::HSVValue color_;
    int player_ = 0;
    Type type_ = Type::STANDARD;

    Stone(wxColor color=wxColor(0, 0, 0), int player=0, Type type=Type::STANDARD) :
        color_(wxImage::RGBtoHSV(wxImage::RGBValue(color.Red(), color.Green(), color.Blue()))), player_(player), type_(type) {
      initStoneImages();
    }

    void paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale) const;
    void setPosition(double x, double y) { x_ = x; y_ = y; }
    bool isLayed() const { return x_ != Card::OUTSIDE; }
    bool isThere(double x, double y);

    friend void to_json(nlohmann::json& j, const Stone& s) {
      j = nlohmann::json{{"x", s.x_}, {"y", s.y_}, {"color", s.color_}, {"player", s.player_}, {"type", s.type_}};
    }
    friend void from_json(const nlohmann::json& j, Stone& s) {
      j.at("x").get_to(s.x_);
      j.at("y").get_to(s.y_);
      j.at("color").get_to(s.color_);
      j.at("player").get_to(s.player_);
      j.at("type").get_to(s.type_);
    }
};


#endif //CARCASONNE_STONE_H
