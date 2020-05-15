//
// Created by ts on 10.05.20.
//

#ifndef KACASSONNE_POINTENTRYDIALOG_H
#define KACASSONNE_POINTENTRYDIALOG_H

#include "PointEntryDialog_B.h"
#include "Player.h"

class PointEntryDialog : public PointEntryDialog_B{
  public:
    int points_;

    PointEntryDialog(wxWindow* parent, int digit, const std::vector<Player>& players, int myself);

    int getPlayer() const { return player_choice_->GetSelection(); }
    bool getAdd() const { return add_checkbox_->GetValue(); }

    virtual void keyDown( wxKeyEvent& event );
    virtual void cancel( wxCommandEvent& event );
    virtual void ok( wxCommandEvent& event );
};

#endif //KACASSONNE_POINTENTRYDIALOG_H
