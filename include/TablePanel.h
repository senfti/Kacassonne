//
// Created by ts on 24.03.20.
//

#ifndef CARCASONNE_TABLEPANEL_H
#define CARCASONNE_TABLEPANEL_H

#include <wx/panel.h>
#include "Card.h"
#include "Stack.h"
#include "Game.h"

class TablePanel : public wxPanel{
  private:
    double scale_ = 1.0;
    wxPoint offset_ = wxPoint(0, 0);
    wxPoint last_position_ = wxPoint(Card::OUTSIDE, Card::OUTSIDE);

    Game* game_;

  public:
    TablePanel(wxWindow *parent, wxWindowID winid = wxID_ANY, const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER,
               const wxString &name = wxPanelNameStr);
    ~TablePanel();

    void setGame(Game* game) { game_ = game; }
    wxPoint2DDouble toGame(const wxPoint& pos) const { return toGame(pos.x, pos.y); }
    wxPoint2DDouble toGame(int x, int y) const;
    wxPoint toTable(const wxPoint2DDouble& pos) const { return toTable(pos.m_x, pos.m_y); }
    wxPoint toTable(double x, double y) const;

    void paint(wxPaintEvent &event);

    virtual void move( wxMouseEvent& event );
    virtual void leave( wxMouseEvent& event );
    virtual void lDown( wxMouseEvent& event );
    virtual void lUp( wxMouseEvent& event );
    virtual void mDown( wxMouseEvent& event );
    virtual void mUp( wxMouseEvent& event );
    virtual void wheel( wxMouseEvent& event );
    virtual void rDown( wxMouseEvent& event );
    virtual void rDDown( wxMouseEvent& event );
    virtual void rUp( wxMouseEvent& event );
};

#endif //CARCASONNE_TABLEPANEL_H
