//
// Created by ts on 28.03.20.
//

#ifndef CARCASONNE_CARD_H
#define CARCASONNE_CARD_H

#include <vector>
#include <list>
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <array>
#include "nlohmann/json.hpp"

class Card{
  public:
    enum class Side {CITY, ROAD, GRAS};
    static constexpr int OUTSIDE = -1000000;
    //enum class SIDE {CITY, ROAD, GRASSLAND};

    static std::string CARD_FOLDER;
    static std::vector<std::pair<wxImage, int>> CARD_IMAGES;
    static std::vector<std::array<Card::Side, 4>> CARD_SIDES;
    static int CARD_IMAGES_SIZE;
    static int cardSize(double scale) { return int(CARD_IMAGES_SIZE*scale/2)*2; }

    static bool initCardImages();

  private:
    int image_nr_ = 11;
    int x_ = OUTSIDE, y_ = OUTSIDE;
    int r_ = 0;

  public:
    Card(int image_nr = 11) : image_nr_(image_nr) {}

    enum class State{CURRENT, PREVIOUS, OTHER, NEXT};

    void paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale, State state=State::OTHER, bool valid=true) const;

    bool valid() const { return image_nr_ >= 0; }
    int x() const { return x_; }
    int y() const { return y_; }
    wxPoint pt() const { return wxPoint(x_, y_); }
    int r() const { return r_; }
    int imageNr() const { return image_nr_; }

    void setPosition(int x, int y) { x_ = x; y_ = y; }
    void rotate() { r_++; }
    void rotate(int r) { r_ = r; }

    friend void to_json(nlohmann::json& j, const Card& c) {
        j = nlohmann::json{{"image_nr", c.image_nr_}, {"x", c.x_}, {"y", c.y_}, {"r", c.r_}};
    }
    friend void from_json(const nlohmann::json& j, Card& c) {
        j.at("image_nr").get_to(c.image_nr_);
        j.at("x").get_to(c.x_);
        j.at("y").get_to(c.y_);
        j.at("r").get_to(c.r_);
    }
};

#endif //CARCASONNE_CARD_H
