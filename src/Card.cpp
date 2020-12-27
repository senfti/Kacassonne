//
// Created by ts on 28.03.20.
//
#include "Card.h"
#include <fstream>
#include <tuple>
#include <algorithm>
#include <filesystem>


std::string Card::CARD_FOLDER = "./";
std::vector<Card::CardImage> Card::CARD_IMAGES;
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
        std::array<Card::Side, 4> sides;
        sides[0] = it.value()["sides"]["top"].get<Card::Side>();
        sides[1] = it.value()["sides"]["left"].get<Card::Side>();
        sides[2] = it.value()["sides"]["bottom"].get<Card::Side>();
        sides[3] = it.value()["sides"]["right"].get<Card::Side>();
        CARD_IMAGES.push_back(CardImage(it.key(), sides, it.value()["idx"]));
        if(it.value()["special"].get<std::string>() == "start"){
          std::swap(CARD_IMAGES.back(), CARD_IMAGES.front());
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

std::map<std::string, std::map<std::string, int>> Card::loadCardCounts(){
  const char *env = std::getenv("CARD_FOLDER");
  if(env)
    CARD_FOLDER = env;
  else
    CARD_FOLDER = "data/cards/";
  if(CARD_FOLDER.back() != '/')
    CARD_FOLDER += "/";

  std::map<std::string, std::map<std::string, int>> card_counts;
  for (auto& p : std::filesystem::directory_iterator(CARD_FOLDER)) {
    if (p.path().extension().string() == ".txt") {
      std::string name = p.path().filename().string();
      name = name.substr(0, name.size() - 4);
      card_counts.insert({name, std::map<std::string, int>()});
      std::ifstream f(p.path().string());
      std::string cn;
      int cnt;
      while(f >> cn >> cnt)
        card_counts[name].insert({cn, cnt});
    }
  }
  return card_counts;
}

void Card::paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale, State state, bool valid) const {
  if(image_nr_ >= int(Card::CARD_IMAGES.size())){
    return;
  }
  int edge_length = cardSize(scale);
  int border = std::min(std::max(1, edge_length/48), 2);
  wxImage tmp = Card::CARD_IMAGES[image_nr_].image_.Scale(edge_length - 2*border, edge_length - 2*border);
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
    wxPen invalid_pen(wxColor(0xFF, 0x00, 0x00), 3*scale, wxPENSTYLE_SOLID);
    dc.SetPen(invalid_pen);
    dc.DrawLine(pos, pos + wxPoint(edge_length, edge_length));
  }
}