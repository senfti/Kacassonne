//
// Created by ts on 24.03.20.
//

#ifndef CARCASONNE_POINTGROUP_H
#define CARCASONNE_POINTGROUP_H

#include <wx/wx.h>
#include <vector>
#include <wx/valnum.h>
#include "Connection.h"

class PointGroup : public wxBoxSizer{
  public:
    PointGroup(const wxString& name, const wxColor& color, bool highlight, wxWindow* parent);

    void setActive(bool active, bool card_active);
    void setPoints(int points);
    void setStones(int stones);
    void setOldPoints(int points);

  protected:
    wxPanel* active_panel_ = nullptr;
    wxStaticText* name_field_ = nullptr;
    wxStaticText* stones_field_ = nullptr;
    wxStaticText* point_field_ = nullptr;
    wxStaticText* old_points_field_ = nullptr;
};

#endif //CARCASONNE_POINTGROUP_H
