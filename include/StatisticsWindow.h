//
// Created by thomas on 29.12.20.
//

#ifndef KACASSONNE_STATISTICSWINDOW_H
#define KACASSONNE_STATISTICSWINDOW_H

#include "StatisticsWindow_B.h"

#include <vector>
#include <tuple>


class StatisticsWindow : public StatisticsWindow_B{
  public:
    std::vector<std::tuple<wxString, wxColor, std::vector<int>>> pts_;

    StatisticsWindow(wxWindow* parent,
                     const std::tuple<std::vector<wxString>, std::vector<wxString>, std::vector<std::vector<int>>>& stats,
                     const std::vector<std::tuple<wxString, wxColor, std::vector<int>>>& pts);

    virtual void paint( wxPaintEvent& event );
};

#endif //KACASSONNE_STATISTICSWINDOW_H
