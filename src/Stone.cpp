//
// Created by ts on 28.03.20.
//

#include "Stone.h"
#include <filesystem>

std::vector<wxImage> Stone::STONE_IMAGES;

bool Stone::initStoneImages(){
  if(STONE_IMAGES.empty()){
    const char* env = std::getenv("STONE_FOLDER");
    std::string stone_folder = "data/stones/";
    if(env)
      stone_folder = env;
    if(stone_folder.back() != '/')
      stone_folder += "/";

    std::vector<std::string> fns;
    for (auto& p : std::filesystem::directory_iterator(stone_folder)) {
      if(p.path().extension().string() == ".png") {
        fns.push_back(p.path().filename().string());
      }
    }
    std::sort(fns.begin(), fns.end());

    wxInitAllImageHandlers();
    for(auto cf : fns){
      STONE_IMAGES.push_back(wxImage(stone_folder + cf));
    }
  }
  return STONE_IMAGES.size();
}


void Stone::paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale) const{
  if(player_ < int(STONE_IMAGES.size())){
    int size = SIZE*Card::cardSize(scale);
    wxImage tmp = STONE_IMAGES[player_].Scale(2*size, 2*size);
    dc.DrawBitmap(wxBitmap(tmp), pos - wxPoint(size, size));
  }
  else{
    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(wxBrush(color_));
    dc.DrawCircle(pos, SIZE * Card::cardSize(scale));
  }
}


bool Stone::isThere(double x, double y){
  return (std::sqrt((x-x_)*(x-x_) + (y-y_)*(y-y_)) < SIZE);
}
