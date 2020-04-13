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

class MyApp;

class MainFrame : public MainFrame_B{
  protected:
    MyApp* app_;
    Game* game_;
    std::vector<PointGroup*> players_guis_;
    wxTimer timer_;

    virtual void quit( wxCommandEvent& event );
    virtual void next( wxCommandEvent& event );
    virtual void back( wxCommandEvent& event );
    virtual void shuffle( wxCommandEvent& event );
    virtual void restart( wxCommandEvent& event );

    void OnTimer(wxTimerEvent& event);

  public:
    MainFrame(MyApp* app);

    void setGame(Game* game, bool restart=false);
    void setCurrentPlayer(int64_t player);

    virtual void next();
};

#endif //CARCASONNE_MAINFRAME_H
