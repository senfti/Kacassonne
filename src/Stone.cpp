//
// Created by ts on 28.03.20.
//

#include "Stone.h"


void Stone::paint(wxAutoBufferedPaintDC& dc, const wxPoint& pos, double scale) const{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(wxBrush(color_));
  dc.DrawCircle(pos, SIZE*Card::CARD_IMAGES_SIZE*scale);
}


bool Stone::isThere(double x, double y){
  return (std::sqrt((x-x_)*(x-x_) + (y-y_)*(y-y_)) < SIZE);
}
