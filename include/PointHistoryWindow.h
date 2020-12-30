//
// Created by ts on 31.05.20.
//

#ifndef KACASSONNE_POINTHISTORYWINDOW_H
#define KACASSONNE_POINTHISTORYWINDOW_H

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <vector>
#include "Player.h"

class PointHistoryWindow : public wxFrame
{
  private:

  protected:
    wxButton* hide_button_;
    wxGrid* pts_grid_;
    std::vector<int> point_count_;
    std::vector<int> last_points_;
    int pt_number_ = 0;

  public:

    PointHistoryWindow( wxWindow* parent, const std::vector<Player>& players,
      wxWindowID id = wxID_ANY, const wxString& title = wxT("Point History"), const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxSTAY_ON_TOP|wxTAB_TRAVERSAL);

    ~PointHistoryWindow();

    void setPoints(int player, int points);
    virtual void hide( wxCommandEvent& event ){
      Show(false);
    }
};



#endif //KACASSONNE_POINTHISTORYWINDOW_H
