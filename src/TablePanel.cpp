//
// Created by ts on 24.03.20.
//

#include "TablePanel.h"
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <TablePanel.h>
#include <filesystem>
#include <PointEntryDialog.h>
#include "MainFrame.h"


TablePanel::TablePanel(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    : wxPanel(parent, winid, pos, size, style, name) {
  SetBackgroundColour(wxColor(188,188,188));
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
  Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( TablePanel::keyDown ), NULL, this );
  Connect( wxEVT_KEY_UP, wxKeyEventHandler( TablePanel::keyUp ), NULL, this );
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
  Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( TablePanel::keyDown ), NULL, this );
  Disconnect( wxEVT_KEY_UP, wxKeyEventHandler( TablePanel::keyUp ), NULL, this );
}

wxPoint2DDouble TablePanel::toGame(int x, int y) const {
  return wxPoint2DDouble((x - offset_.x) / double(Card::cardSize(scale_)),
                         (y - offset_.y) / double(Card::cardSize(scale_)));
}

wxPoint TablePanel::toTable(double x, double y) const {
  double edge_length = Card::cardSize(scale_);
  return offset_ + wxPoint(x*edge_length, y*edge_length);
}

void TablePanel::checkFlip(){
  if(getTime() >= down_time_ + FLIP_TIMEOUT){
    if(game_->flipCard()){
      flipped_ = true;
      down_time_ = 9999999999;
      Refresh();
    }
  }
}

void TablePanel::paint(wxPaintEvent &event){
  wxAutoBufferedPaintDC dc(this);
  dc.Clear();
  {
    std::lock_guard<std::mutex> lock(game_->data_lock_);
    for(const auto &card : game_->played_cards_){
      card.paint(dc, toTable(card.x(), card.y()), scale_, &card == &(game_->played_cards_.back()) ? Card::State::PREVIOUS : Card::State::OTHER);
    }
    if(game_->current_card_ && game_->current_card_->x() != Card::OUTSIDE){
      game_->current_card_->paint(dc, toTable(game_->current_card_->x(), game_->current_card_->y()), scale_,
                                  Card::State::CURRENT, game_->validPosition());
    }
    for(const auto &p : game_->players_){
      for(const auto &s : p.stones_){
        s.paint(dc, toTable(s.x_, s.y_), scale_);
      }
    }
    for(const auto &f : game_->flares_){
      if(f.isDraw() && !f.isTimeout()){
        dc.SetPen(wxPen(game_->players_[f.player_].color_, std::max(1.0, 3 * scale_)));
        int l = scale_ * 10;
        wxPoint pos = toTable(f.x_, f.y_);
        dc.DrawLine(pos.x - l, pos.y - l, pos.x + l, pos.y + l);
        dc.DrawLine(pos.x - l, pos.y + l, pos.x + l, pos.y - l);
      }
    }
    for(size_t i=0; i<game_->count_marks_.size(); i++){
      dc.SetFont(wxFont(int(16 * scale_), wxFONTFAMILY_DEFAULT, wxFontStyle::wxFONTSTYLE_NORMAL, wxFontWeight::wxFONTWEIGHT_BOLD));
      wxPoint pos = toTable(game_->count_marks_[i].x_, game_->count_marks_[i].y_) - wxPoint(int(12 * scale_), int(12 * scale_));
      dc.DrawText(std::to_string(i+1), pos);
    }
  }
  int cards_left = game_->getLeftCards();
  int player_count = game_->getPlayerCount();
  if(cards_left > 2 * player_count)
    dc.SetTextForeground(wxColor(0, 255, 0));
  else if(cards_left > player_count)
    dc.SetTextForeground(wxColor(255, 165, 0));
  else
    dc.SetTextForeground(wxColor(255, 0, 0));
  dc.SetTextBackground(wxColor(0, 0, 0, 0));
  dc.SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
  wxSize text_size = dc.GetTextExtent(std::to_string(cards_left));
  int width = text_size.GetWidth();
  int x_start = GetClientSize().GetWidth() - width;
  int height = text_size.GetHeight();
  dc.SetBrush(*wxWHITE_BRUSH);
  dc.SetPen(*wxWHITE_PEN);
  dc.DrawRectangle(x_start - 2, 0, GetClientSize().GetWidth(), height);
  dc.DrawText(std::to_string(cards_left), x_start, 0);
}

void TablePanel::move(wxMouseEvent &event){
  SetFocus();
  if(event.m_middleDown || event.ControlDown()){
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
  SetFocus();
}

void TablePanel::lUp(wxMouseEvent &event){
  wxPoint2DDouble pos = toGame(event.GetPosition());
  if(count_mode_){
    game_->addMark(pos.m_x, pos.m_y);
    Refresh();
  }
  else if(game_->layCard() || game_->moveStone(pos.m_x, pos.m_y, event.ShiftDown() ? Stone::Type::HORSE : Stone::Type::STANDARD))
    Refresh();
}

void TablePanel::mDown(wxMouseEvent &event){
  last_position_ = event.GetPosition();
}

void TablePanel::mUp(wxMouseEvent &event){
  last_position_ = wxPoint(Card::OUTSIDE, Card::OUTSIDE);
}

void TablePanel::wheel(wxMouseEvent &event){
  double s = (event.GetWheelRotation() > 0 ? std::sqrt(2.0) : std::sqrt(0.5));
  if(scale_ < 0.6 && s < 1)
    return;
  if(scale_ >= 4 && s > 1)
    return;
  wxPoint2DDouble game_pos = toGame(event.GetPosition());
  scale_ *= s;
  wxPoint2DDouble tmp = game_pos*Card::cardSize(scale_);
  offset_ = event.GetPosition() - wxPoint(tmp.m_x, tmp.m_y);
  Refresh();
}

void TablePanel::rDown(wxMouseEvent &event){
  down_time_ = getTime();
  flipped_ = false;
  if(!game_->cardInHand())
    game_->flare(wxPoint2DDouble(toGame(event.GetPosition())));
}

void TablePanel::rDDown( wxMouseEvent& event ){
  rDown(event);
}

void TablePanel::rUp(wxMouseEvent &event){
  down_time_ = 9999999999;
  if(!flipped_)
    if(game_->rotateCard())
      Refresh();
}

void TablePanel::keyDown( wxKeyEvent& event ){
  if((event.GetKeyCode() == '-') || event.GetKeyCode() == WXK_NUMPAD_SUBTRACT ||
        (event.GetKeyCode() >= 48 && event.GetKeyCode() < 58) || (event.GetKeyCode() >= WXK_NUMPAD0 && event.GetKeyCode() <= WXK_NUMPAD9)){
    int digit = (event.GetKeyCode() == '-' || event.GetKeyCode() == WXK_NUMPAD_SUBTRACT? -1 :
        (event.GetKeyCode() >= 48 && event.GetKeyCode() < 58 ? event.GetKeyCode() - 48 : event.GetKeyCode() - WXK_NUMPAD0));
    PointEntryDialog pd(this, digit, game_->getPlayers(), game_->connection_->player_number_);
    if(pd.ShowModal() == 0){
      game_->setPoints(pd.getPlayer(), pd.points_, pd.getAdd(), true);
    }
  }

  if(event.GetKeyCode() == WXK_CONTROL)
    last_position_ = event.GetPosition();
  else if(event.GetKeyCode() == WXK_RETURN){
    MainFrame* parent = dynamic_cast<MainFrame*>(GetParent());
    if(parent)
      parent->next();
  }
  else if(event.GetKeyCode() == 'F')
    game_->flare(wxPoint2DDouble(toGame(event.GetPosition())), true);
  else if(event.GetKeyCode() == 'P'){
    wxPoint2DDouble pos = toGame(event.GetPosition());
    if(game_->moveStone(pos.m_x, pos.m_y, Stone::Type::STANDARD, true))
      Refresh();
  }
  else if(event.GetKeyCode() == 'H'){
    wxPoint2DDouble pos = toGame(event.GetPosition());
    if(game_->moveStone(pos.m_x, pos.m_y, Stone::Type::HORSE, true))
      Refresh();
  }
  else if(event.GetKeyCode() == 'R'){
    if(game_->rotateCard())
      Refresh();
  }
  else if(event.GetKeyCode() == 'M'){
    if(game_->flipCard()){
      flipped_ = true;
      down_time_ = 9999999999;
      Refresh();
    }
  }
  else if(event.GetKeyCode() == 'C'){
    if(count_mode_){
      game_->setMarks();
      Refresh();
    }
    count_mode_ = !count_mode_;
  }
  else if(event.GetKeyCode() == 'W'){
    MainFrame* parent = dynamic_cast<MainFrame*>(GetParent());
    if(parent){
      wxCommandEvent evt;
      parent->togglePointHistory(evt);
    }
  }
  else if(count_mode_ && event.GetKeyCode() == 'X'){
    game_->removeMark();
    Refresh();
  }
}

void TablePanel::keyUp( wxKeyEvent& event ){
  if(event.GetKeyCode() == WXK_CONTROL)
    last_position_ = wxPoint(Card::OUTSIDE, Card::OUTSIDE);
}

