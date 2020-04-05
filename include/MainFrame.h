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

class MainFrame : public MainFrame_B{
  protected:
    Game* game_;
    std::vector<PointGroup*> players_guis_;
    wxTimer timer_;

    virtual void startServer( wxCommandEvent& event );
    virtual void connect( wxCommandEvent& event );
    virtual void quit( wxCommandEvent& event );
    virtual void undo( wxCommandEvent& event );
    virtual void next( wxCommandEvent& event );
    virtual void back( wxCommandEvent& event );
    virtual void shuffle( wxCommandEvent& event );

    void OnTimer(wxTimerEvent& event);

  public:
    MainFrame();

    void setGame(Game* game);
    void setCurrentPlayer(int player);
};

#endif //CARCASONNE_MAINFRAME_H
