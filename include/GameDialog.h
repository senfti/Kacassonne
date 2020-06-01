//
// Created by ts on 31.03.20.
//

#ifndef CARCASONNE_GAMEDIALOG_H
#define CARCASONNE_GAMEDIALOG_H

#include "GameDialog_B.h"
#include "Connection.h"
#include <thread>
#include <mutex>
#include <list>

class GameDialog : public GameDialog_B{
  public:
    GameDialog(Connection *connection);
    ~GameDialog();

    Connection* connection_;
    std::thread* receiver_ = nullptr;
    bool running_ = true;
    std::mutex message_lock_;
    std::list<std::pair<std::string, Message>> pending_messages_;
    bool color_changed_ = false;

    std::vector<bool> ack_;
    wxTimer timer_;
    unsigned long card_number_ = 120;
    bool allow_mirror_ = true;

    std::map<std::string, int> card_count_;
    std::string balance_name_;

    void recv();

    virtual void changeColor( wxCommandEvent& event );
    virtual void changeSettings( wxCommandEvent& event );
    virtual void quit( wxCommandEvent& event );
    virtual void start( wxCommandEvent& event );
    void OnTimer(wxTimerEvent& event);
};

#endif //CARCASONNE_GAMEDIALOG_H
