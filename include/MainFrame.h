//
// Created by ts on 24.03.20.
//

#ifndef CARCASONNE_MAINFRAME_H
#define CARCASONNE_MAINFRAME_H

#include "MainFrame_B.h"
#include "PointGroup.h"
#include "Game.h"
#include "TablePanel.h"
#include <vector>
#include <thread>
#include <mutex>
#include "HelpDialog_B.h"
#include "PointHistoryWindow.h"

class MyApp;

class MainFrame : public MainFrame_B{
  protected:
    MyApp* app_;
    Game* game_;
    std::vector<PointGroup*> players_guis_;
    wxTimer timer_;

    int preview_image_ = -1;
    PointHistoryWindow* pt_history_wnd_;

    virtual void quit( wxCommandEvent& event );
    virtual void next( wxCommandEvent& event );
    virtual void back( wxCommandEvent& event );
    virtual void shuffle( wxCommandEvent& event );
    virtual void restart( wxCommandEvent& event );
    virtual void newGame( wxCommandEvent& event );
    virtual void help( wxCommandEvent& event );
    virtual void showIds( wxCommandEvent& event );

    void OnTimer(wxTimerEvent& event);

  public:
    MainFrame(MyApp* app);

    void setGame(Game* game, bool restart=false);
    void setCurrentPlayer(int player);

    virtual void next();

    void disable();
};

#endif //CARCASONNE_MAINFRAME_H
