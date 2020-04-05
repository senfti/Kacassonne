//
// Created by ts on 29.03.20.
//

#include "Player.h"

Player::Player(int number, const wxString& name)
  : name_(name){
  static std::vector<wxColor> colors = {wxColor(255, 0, 0), wxColor(0, 255, 0), wxColor(0, 0, 255),
                                        wxColor(255, 255, 0), wxColor(255, 0, 255), wxColor(0, 255, 255),
                                        wxColor(0, 0, 0), wxColor(255, 255, 255)};
  if(number >= 0){
    color_ = colors[number];
    for(int i = 0; i < 7; i++){
      stones_.push_back(Stone(colors[number]));
    }
  }
}


void to_json(nlohmann::json& j, const wxColor& c) {
  j = nlohmann::json{{"r", c.Red()}, {"g", c.Green()}, {"b", c.Blue()}, {"a", c.Alpha()}};
}
void from_json(const nlohmann::json& j, wxColor& c) {
  c.Set(j.at("r").get<unsigned char>(), j.at("g").get<unsigned char>(), j.at("b").get<unsigned char>(), j.at("a").get<unsigned char>());
}
