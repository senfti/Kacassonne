//
// Created by thomas on 29.12.20.
//

#include <wx/grid.h>
#include <wx/dcbuffer.h>
#include "StatisticsWindow.h"


StatisticsWindow::StatisticsWindow(wxWindow* parent,
                                   const std::tuple<std::vector<wxString>, std::vector<wxString>, std::vector<std::vector<int>>>& stats,
                                   const std::vector<std::tuple<wxString, wxColor, std::vector<int>>>& pts)
    : StatisticsWindow_B(parent), pts_(pts)
{
  graph_panel_->SetBackgroundStyle(wxBG_STYLE_PAINT);
  const auto& [col_labels, row_labels, data] = stats;
  stats_grid_->AppendRows(row_labels.size());
  for(size_t i=0; i<row_labels.size(); i++){
    stats_grid_->SetRowLabelValue(i, row_labels[i]);
    for(size_t j=0; j<std::min(data[i].size(), size_t(stats_grid_->GetNumberCols())); j++){
      stats_grid_->SetCellValue(i, j, std::to_string(data[i][j]));
    }
  }
  stats_grid_->AutoSize();
  stats_grid_->Refresh();
  Fit();
  Refresh();
}

void StatisticsWindow::paint( wxPaintEvent& event ){
  int maximum = 1;
  for(const auto& p : pts_)
    maximum = std::max(std::get<2>(p).back(), maximum);
  maximum = std::ceil(maximum / 20.0) * 20;
  int py_per_unit = 600 / maximum;
  int height = maximum * py_per_unit;
  int px_per_unit = 600 / std::get<2>(pts_[0]).size();
  int width = std::get<2>(pts_[0]).size() * px_per_unit;

  wxAutoBufferedPaintDC dc(graph_panel_);
  dc.Clear();
  wxSize sz = graph_panel_->GetClientSize();
  wxPoint origin(30, sz.y - 30);
  dc.SetPen(wxPen(wxColor(0,0,0), 1));
  dc.DrawLine(origin, wxPoint(origin.x, origin.y - height));
  dc.DrawLine(origin, wxPoint(origin.x + width, origin.y));
  dc.SetPen(wxPen(wxColor(84, 84, 84), 1));
  for(int y=0; y<height; y+=20*py_per_unit){
    dc.DrawLine(wxPoint(origin.x, origin.y - y), wxPoint(origin.x + width, origin.y - y));
    dc.SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFontStyle::wxFONTSTYLE_NORMAL, wxFontWeight::wxFONTWEIGHT_NORMAL));
    dc.DrawText(std::to_string(y / py_per_unit), 0, origin.y - y - 8);
  }
  for(const auto& p : pts_){
    const auto& [name, color, pts] = p;
    dc.SetPen(wxPen(color, 3));
    wxPoint last_p(0, 0);
    for(const auto& pt : pts){
      wxPoint next_p(last_p.x + px_per_unit, -pt * py_per_unit);
      dc.DrawLine(last_p + origin, next_p + origin);
      last_p = next_p;
    }
  }
}
