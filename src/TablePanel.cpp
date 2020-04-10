//
// Created by ts on 24.03.20.
//

#include "TablePanel.h"
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <TablePanel.h>


TablePanel::TablePanel(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    : wxPanel(parent, winid, pos, size, style, name) {
  SetBackgroundStyle(wxBG_STYLE_PAINT);
  Connect( wxEVT_PAINT, wxPaintEventHandler( TablePanel::paint ), NULL, this );

  Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( TablePanel::leave ), NULL, this );
  Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( TablePanel::lDown ), NULL, this );
  Connect( wxEVT_LEFT_UP, wxMouseEventHandler( TablePanel::lUp ), NULL, this );
  Connect( wxEVT_MIDDLE_DOWN, wxMouseEventHandler( TablePanel::mDown ), NULL, this );
  Connect( wxEVT_MIDDLE_UP, wxMouseEventHandler( TablePanel::mUp ), NULL, this );
  Connect( wxEVT_MOTION, wxMouseEventHandler( TablePanel::move ), NULL, this );
  Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( TablePanel::wheel ), NULL, this );
  Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( TablePanel::rDown ), NULL, this );
  Connect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( TablePanel::rDDown ), NULL, this );
  Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( TablePanel::rUp ), NULL, this );
}


TablePanel::~TablePanel(){
  Disconnect( wxEVT_PAINT, wxPaintEventHandler( TablePanel::paint ), NULL, this );

  Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( TablePanel::leave ), NULL, this );
  Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( TablePanel::lDown ), NULL, this );
  Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( TablePanel::lUp ), NULL, this );
  Disconnect( wxEVT_MIDDLE_DOWN, wxMouseEventHandler( TablePanel::mDown ), NULL, this );
  Disconnect( wxEVT_MIDDLE_UP, wxMouseEventHandler( TablePanel::mUp ), NULL, this );
  Disconnect( wxEVT_MOTION, wxMouseEventHandler( TablePanel::move ), NULL, this );
  Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( TablePanel::wheel ), NULL, this );
  Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( TablePanel::rDown ), NULL, this );
  Disconnect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( TablePanel::rDDown ), NULL, this );
  Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( TablePanel::rUp ), NULL, this );
}

wxPoint2DDouble TablePanel::toGame(int x, int y) const {
  return wxPoint2DDouble((x - offset_.x) / double(Card::CARD_IMAGES_SIZE) / scale_,
                         (y - offset_.y) / double(Card::CARD_IMAGES_SIZE) / scale_);
}

wxPoint TablePanel::toTable(double x, double y) const {
  double edge_length = Card::CARD_IMAGES_SIZE*scale_;
  return offset_ + wxPoint(x*edge_length, y*edge_length);
}

void TablePanel::paint(wxPaintEvent &event){
  wxAutoBufferedPaintDC dc(this);
  dc.Clear();
  std::lock_guard<std::mutex> lock(game_->data_lock_);
  for(const auto& card : game_->played_cards_){
    card.paint(dc, toTable(card.x(), card.y()), scale_);
  }
  if(game_->current_card_ && game_->current_card_->x() != Card::OUTSIDE){
    game_->current_card_->paint(dc, toTable(game_->current_card_->x(), game_->current_card_->y()), scale_,
      game_->validPosition());
  }
  for(const auto& p : game_->players_){
    for(const auto& s : p.stones_){
      s.paint(dc, toTable(s.x_, s.y_), scale_);
    }
  }
}

void TablePanel::move(wxMouseEvent &event){
  if(event.m_middleDown){
    if(last_position_.x != Card::OUTSIDE){
      offset_ += event.GetPosition() - last_position_;
      Refresh();
    }
    last_position_ = event.GetPosition();
  }
  wxPoint2DDouble pos = toGame(event.GetPosition());
  if(game_->moveCard(pos.m_x, pos.m_y))
    Refresh();
}

void TablePanel::leave(wxMouseEvent &event){
  last_position_ = wxPoint(Card::OUTSIDE, Card::OUTSIDE);
}

void TablePanel::lDown(wxMouseEvent &event){
}

void TablePanel::lUp(wxMouseEvent &event){
  wxPoint2DDouble pos = toGame(event.GetPosition());
  if(game_->layCard() || game_->moveStone(pos.m_x, pos.m_y))
    Refresh();
}

void TablePanel::mDown(wxMouseEvent &event){
  last_position_ = event.GetPosition();
}

void TablePanel::mUp(wxMouseEvent &event){
  last_position_ = wxPoint(Card::OUTSIDE, Card::OUTSIDE);
}

void TablePanel::wheel(wxMouseEvent &event){
  double s = (event.GetWheelRotation() > 0 ? 2.0 : 0.5);
  if(scale_ < 0.3 && s < 1)
    return;
  if(scale_ >= 4 && s > 1)
    return;
  scale_ *= s;
  offset_ = event.GetPosition() - (event.GetPosition() - offset_) * s;
  Refresh();
}

void TablePanel::rDown(wxMouseEvent &event){
  if(game_->rotateCard())
    Refresh();
}

void TablePanel::rDDown( wxMouseEvent& event ){
  rDown(event);
}

void TablePanel::rUp(wxMouseEvent &event){

}
