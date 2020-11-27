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
    int pt_history_wnd_id_ = -1;

    virtual void quit( wxCommandEvent& event );
    virtual void next( wxCommandEvent& event );
    virtual void back( wxCommandEvent& event );
    virtual void shuffle( wxCommandEvent& event );
    virtual void restart( wxCommandEvent& event );
    virtual void newGame( wxCommandEvent& event );
    virtual void help( wxCommandEvent& event );
    virtual void showIds( wxCommandEvent& event );
    virtual void close( wxCloseEvent& event ) { takeScreenshot(""); Destroy(); }
    virtual void screenshot( wxCommandEvent& event ) { takeScreenshot(""); }
    virtual void viewSettings( wxCommandEvent& event );

    void OnTimer(wxTimerEvent& event);

  public:
    MainFrame(MyApp* app);
    ~MainFrame();

    void setGame(Game* game, bool restart=false);
    void setCurrentPlayer(int player);

    virtual void next();

    void disable();

    void takeScreenshot(const std::string& prefix);
    virtual void togglePointHistory( wxCommandEvent& event ) {
      if(FindWindowById(pt_history_wnd_id_))
        pt_history_wnd_->Show(!pt_history_wnd_->IsShown());
    }
};

#endif //CARCASONNE_MAINFRAME_H
