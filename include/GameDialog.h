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

    std::vector<bool> ack_;
    bool finished_ = false;
    wxTimer timer_;

    void recv();

    virtual void quit( wxCommandEvent& event );
    virtual void start( wxCommandEvent& event );
    void OnTimer(wxTimerEvent& event);
};

#endif //CARCASONNE_GAMEDIALOG_H
