//
// Created by ts on 03.04.20.
//

#ifndef CARCASONNE_LOBBYDIALOG_H
#define CARCASONNE_LOBBYDIALOG_H

#include <mutex>
#include <thread>
#include <list>
#include "LobbyDialog_B.h"
#include "Connection.h"

class LobbyDialog : public LobbyDialog_B{
  public:
    struct GameToJoin{
      std::string name_;
      int64_t id_;
      int64_t host_;
      std::vector<PlayerCon> players_;
      double last_msg_time_ = 0.0;
      wxButton* button_ = nullptr;

      GameToJoin(const std::string& name, int64_t id, int64_t host, const std::vector<PlayerCon>& players, wxWindow* parent)
            : name_(name), id_(id), host_(host), players_(players), button_(new wxButton(parent, wxID_ANY, wxString("Join Game \"" + name_ + "\""))) {
          button_->SetMinSize(wxSize(-1,24));
      }
      ~GameToJoin() {
          delete button_; }
      bool isButtonID(int id) const { return button_->GetId() == id; }
    };

    Connection* connection_;
    std::thread* receiver_ = nullptr;
    bool running_ = true;
    std::list<GameToJoin> games_;
    bool during_reconnect_ = false;
    Message reconnect_reply_ = Message();
    wxString tmp_game_name_;

    std::mutex message_lock_;
    std::list<std::pair<std::string, Message>> pending_messages_;
    wxTimer timer_;

    LobbyDialog(Connection* connection);
    ~LobbyDialog();

    virtual void create( wxCommandEvent& event );
    virtual void reconnect( wxCommandEvent& event );
    virtual void load( wxCommandEvent& event );
    virtual void join( wxCommandEvent& event );
    void OnTimer(wxTimerEvent& event);

    void recv();
};

#endif //CARCASONNE_LOBBYDIALOG_H
