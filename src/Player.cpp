//
// Created by ts on 29.03.20.
//

#include "Player.h"

Player::Player(int number, const wxString& name)
  : name_(name){
  static std::vector<wxColor> colors = {wxColor(220, 0, 0), wxColor(20, 20, 230), wxColor(245, 245, 40), wxColor(40, 40, 50),
                                        wxColor(255, 255, 255), wxColor(40, 220, 40), wxColor(192, 0, 255), wxColor(0, 255, 255),
                                        wxColor(255, 153, 0), wxColor(255, 0, 153), wxColor(180, 255, 0), wxColor(120, 120, 120)};
  if(number >= 0){
    if(number < int(colors.size()))
      color_ = colors[number];
    else{
      srand(time(nullptr));
      color_ = wxColor(rand() % 256, rand() % 256, rand() % 256);
    }
    for(int i = 0; i < 7; i++){
      stones_.push_back(Stone(color_, number, Stone::Type::STANDARD));
    }
    for(int i = 0; i < 1; i++){
      stones_.push_back(Stone(color_, number, Stone::Type::HORSE));
    }
  }
}

int Player::getRemainingStones(Stone::Type type) const{
  int layed_stones = 0;
  for(const auto& s : stones_){
    if(s.isLayed() || (type != Stone::Type::ANY && s.type_ != type))
      layed_stones++;
  }
  return int(stones_.size()) - layed_stones;
}

void to_json(nlohmann::json& j, const wxColor& c) {
  j = nlohmann::json{{"r", c.Red()}, {"g", c.Green()}, {"b", c.Blue()}, {"a", c.Alpha()}};
}
void from_json(const nlohmann::json& j, wxColor& c) {
  c.Set(j.at("r").get<unsigned char>(), j.at("g").get<unsigned char>(), j.at("b").get<unsigned char>(), j.at("a").get<unsigned char>());
}

void to_json(nlohmann::json& j, const wxImage::HSVValue& c){
  j = nlohmann::json{{"h", c.hue}, {"s", c.saturation}, {"v", c.value}};
}
void from_json(const nlohmann::json& j, wxImage::HSVValue& c){
  j.at("h").get_to(c.hue);
  j.at("s").get_to(c.saturation);
  j.at("v").get_to(c.value);
}