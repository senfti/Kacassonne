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
    enum class Side {CITY, ROAD, MEADOW};
    class CardImage{
      public:
        std::string name_;
        wxImage image_;
        std::array<Card::Side, 4> sides_;
        int idx_;

        CardImage(const std::string& name, const std::array<Card::Side, 4>& sides, int idx)
            : name_(name), image_(CARD_FOLDER + name), sides_(sides), idx_(idx){
        }
        friend bool operator<(const CardImage &c1, const CardImage &c2) { return c1.idx_ < c2.idx_; }
    };


    friend void from_json(const nlohmann::json& j, Side& s) { s = (j.get<std::string>() == "city" ? Side::CITY : (j.get<std::string>() == "road" ? Side::ROAD : Side::MEADOW)); }
    static constexpr int OUTSIDE = -1000000;

    static std::string CARD_FOLDER;
    static std::vector<CardImage> CARD_IMAGES;
    static int CARD_IMAGES_SIZE;
    static int cardSize(double scale) { return int(CARD_IMAGES_SIZE*scale/2)*2; }

    static bool initCardImages();
    static std::map<std::string, std::map<std::string, int>> loadCardCounts();

  private:
    int image_nr_ = 11;
    int x_ = OUTSIDE, y_ = OUTSIDE;
    int r_ = 0;
    bool flipped_ = false;

  public:
    Card(int image_nr = 11) : image_nr_(image_nr) {}

    enum class State{CURRENT, PREVIOUS, OTHER, NEXT};

    void paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale, State state=State::OTHER, bool valid=true) const;

    bool valid() const { return image_nr_ >= 0; }
    int x() const { return x_; }
    int y() const { return y_; }
    wxPoint pt() const { return wxPoint(x_, y_); }
    int r() const { return r_ % 4; }
    int flipped() const { return flipped_; }
    int imageNr() const { return image_nr_; }

    void setPosition(int x, int y) { x_ = x; y_ = y; }
    void rotate() { r_ += 1; }
    void flip() { flipped_ = !flipped_; }

    friend void to_json(nlohmann::json& j, const Card& c) {
        j = nlohmann::json{{"image_nr", c.image_nr_}, {"x", c.x_}, {"y", c.y_}, {"r", c.r_}, {"flipped", c.flipped_}};
    }
    friend void from_json(const nlohmann::json& j, Card& c) {
        j.at("image_nr").get_to(c.image_nr_);
        j.at("x").get_to(c.x_);
        j.at("y").get_to(c.y_);
        j.at("r").get_to(c.r_);
        j.at("flipped").get_to(c.flipped_);
    }
};

#endif //CARCASONNE_CARD_H
