//
// Created by ts on 24.03.20.
//

#ifndef CARCASONNE_MAIN_H
#define CARCASONNE_MAIN_H

#include <wx/wx.h>
#include "MainFrame.h"


//Main class for the application (this also implements the main methode)
class MyApp : public wxApp{
  private:
    MainFrame* main_frame_ = nullptr;
    Game* game_ = nullptr;
    Connection* connection_ = nullptr;

  public:
    MyApp(){}
    ~MyApp(){ delete game_; delete connection_;}
    virtual bool OnInit();
    virtual int OnExit();

    std::tuple<int, std::map<std::string, int>, bool, Message> lobbyStuff();
    bool initGame(int card_number, const std::map<std::string, int>& card_count, bool allow_mirror, const Message& reconnect_reply);
    bool reset(bool to_lobby);
};

extern MyApp* my_app;

#endif //CARCASONNE_MAIN_H
