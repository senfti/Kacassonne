//
// Created by ts on 01.06.20.
//

#ifndef KACASSONNE_SETTINGSWINDOW_H
#define KACASSONNE_SETTINGSWINDOW_H


#include "SettingsWindow_B.h"

class SettingsWindow : public SettingsWindow_B{
  public:
    SettingsWindow(wxWindow* parent, const std::map<std::string, int>* current_card_count = nullptr);

    std::map<std::string, std::map<std::string, int>> all_card_counts_;
    std::map<std::string, int> current_count_;
    std::map<std::string, wxTextCtrl*> count_textctrls_;
    std::string balance_name_ = "default";

    virtual void changeSetting( wxCommandEvent& event );
    virtual void save( wxCommandEvent& event );
    virtual void ok( wxCommandEvent& event );
};

#endif //KACASSONNE_SETTINGSWINDOW_H
