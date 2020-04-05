//
// Created by ts on 28.03.20.
//
#include "Card.h"
#include <fstream>
#include <tuple>
#include <algorithm>


std::string Card::CARD_FOLDER = "./";
std::vector<std::pair<wxImage, int>> Card::CARD_IMAGES;
int Card::CARD_IMAGES_SIZE;


bool Card::initCardImages(){
  const char* env = std::getenv("CARD_FOLDER");
  if(env)
    CARD_FOLDER = env;
  else
    CARD_FOLDER = "data/";
  if(CARD_FOLDER.back() != '/')
    CARD_FOLDER += "/";

  if(CARD_IMAGES.empty()){
    wxInitAllImageHandlers();
    std::ifstream file(CARD_FOLDER + "Count.txt");
    for(int i=0; i<24; i++){
      std::string fn;
      int count;
      file >> fn >> count;
      CARD_IMAGES.push_back({wxImage(CARD_FOLDER + fn), count});
    }
  }
  CARD_IMAGES_SIZE = CARD_IMAGES.front().first.GetSize().x;
  return true;
}

void Card::paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale, bool valid) const {
  int edge_length = CARD_IMAGES_SIZE*scale;
  wxImage tmp = Card::CARD_IMAGES[image_nr_].first.Scale(edge_length, edge_length);
  switch(r_ % 4){
    case 1: tmp = tmp.Rotate90(); break;
    case 2: tmp = tmp.Rotate180(); break;
    case 3: tmp = tmp.Rotate90(false); break;
  }
  dc.DrawBitmap(wxBitmap(tmp), pos);
  if(!valid){
    wxPen invalid_pen(wxColor(0xFF, 0x00, 0x00, 0), 3*scale, wxPENSTYLE_SOLID);
    dc.SetPen(invalid_pen);
    dc.DrawLine(pos, pos + wxPoint(edge_length, edge_length));
  }
}