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

    wxInitAllImageHandlers();
    if(std::filesystem::exists(stone_folder + "stone.png")){
      STONE_IMAGES.push_back(wxImage(stone_folder + "stone.png"));
    }
  }
  return STONE_IMAGES.size();
}


void Stone::paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale) const{
  int size = SIZE*Card::cardSize(scale);
  wxImage tmp = STONE_IMAGES[0].Scale(2*size, 2*size);
  for(int x=0; x<tmp.GetWidth(); x++){
    for(int y=0; y<tmp.GetHeight(); y++){
      wxImage::HSVValue hsv = wxImage::RGBtoHSV(wxImage::RGBValue(tmp.GetRed(x,y), tmp.GetGreen(x,y), tmp.GetBlue(x,y)));
      hsv.hue = color_.hue;
      hsv.saturation *= color_.saturation;
      hsv.value *= color_.value;
      wxImage::RGBValue rgb = wxImage::HSVtoRGB(hsv);
      tmp.SetRGB(x, y, rgb.red, rgb.green, rgb.blue);
    }
  }
  dc.DrawBitmap(wxBitmap(tmp), pos - wxPoint(size, size));
}


bool Stone::isThere(double x, double y){
  return (std::sqrt((x-x_)*(x-x_) + (y-y_)*(y-y_)) < SIZE);
}
