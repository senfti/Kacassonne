//
// Created by ts on 28.03.20.
//
#include "Card.h"
#include <fstream>
#include <tuple>
#include <algorithm>
#include <filesystem>


std::string Card::CARD_FOLDER = "./";
std::vector<wxImage> Card::CARD_IMAGES;
std::vector<std::array<Card::Side, 4>> Card::CARD_SIDES;
int Card::CARD_IMAGES_SIZE = 48;


std::array<Card::Side, 4> sidesFromString(const std::string& s){
  std::array<Card::Side, 4> sides;
  for(int i=1; i<5; i++){
    sides[i-1] = (s[i] == 'F' ? Card::Side::MEADOW : (s[i] == 'S' ? Card::Side::CITY : Card::Side::ROAD));
  }
  return sides;
}


bool Card::initCardImages(){
  if(CARD_IMAGES.empty()){
    const char *env = std::getenv("CARD_FOLDER");
    if(env)
      CARD_FOLDER = env;
    else
      CARD_FOLDER = "data/cards/";
    if(CARD_FOLDER.back() != '/')
      CARD_FOLDER += "/";

    try{
      wxInitAllImageHandlers();
      std::ifstream ifs(CARD_FOLDER + "card_data.json");
      nlohmann::json card_data = nlohmann::json::parse(ifs);
      for(auto it : card_data.items()){
        CARD_IMAGES.push_back(wxImage(CARD_FOLDER + it.key()));
        std::array<Card::Side, 4> sides;
        sides[0] = it.value()["sides"]["top"].get<Card::Side>();
        sides[1] = it.value()["sides"]["left"].get<Card::Side>();
        sides[2] = it.value()["sides"]["bottom"].get<Card::Side>();
        sides[3] = it.value()["sides"]["right"].get<Card::Side>();
        CARD_SIDES.push_back(sides);
        if(it.value()["special"].get<std::string>() == "start"){
          std::swap(CARD_IMAGES.back(), CARD_IMAGES.front());
          std::swap(CARD_SIDES.back(), CARD_SIDES.front());
        }
      }
    }
    catch(std::exception &e){
      std::cout << "Failed to load card images and data!" << std::endl;
      return 0;
    }
  }
  return CARD_IMAGES.size();
}

void Card::paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale, State state, bool valid) const {
  int edge_length = cardSize(scale);
  int border = std::min(std::max(1, edge_length/48), 2);
  wxImage tmp = Card::CARD_IMAGES[image_nr_].Scale(edge_length - 2*border, edge_length - 2*border);
  if(flipped_)
    tmp = tmp.Mirror();
  switch(r_ % 4){
    case 1: tmp = tmp.Rotate90(); break;
    case 2: tmp = tmp.Rotate180(); break;
    case 3: tmp = tmp.Rotate90(false); break;
  }
  if(state != State::OTHER && valid){
    dc.SetBrush(state == State::CURRENT ? *wxGREEN_BRUSH : *wxYELLOW_BRUSH);
    dc.SetPen(state == State::CURRENT ? *wxGREEN_PEN : *wxYELLOW_PEN);
    dc.DrawRectangle(pos - wxPoint(border, border), wxSize(edge_length + 2*border, edge_length + 2*border));
  }
  dc.DrawBitmap(wxBitmap(tmp), pos + wxPoint(border, border));
  if(!valid){
    wxPen invalid_pen(wxColor(0xFF, 0x00, 0x00, 0), 3*scale, wxPENSTYLE_SOLID);
    dc.SetPen(invalid_pen);
    dc.DrawLine(pos, pos + wxPoint(edge_length, edge_length));
  }
}