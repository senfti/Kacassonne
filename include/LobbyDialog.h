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
      long id_;
      long host_;
      std::vector<std::pair<long, std::string>> players_;
      wxButton* button_ = nullptr;

      GameToJoin(const std::string& name, long id, long host, const std::vector<std::pair<long, std::string>>& players, wxWindow* parent)
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

    std::mutex message_lock_;
    std::list<std::pair<std::string, Message>> pending_messages_;
    wxTimer timer_;

    LobbyDialog(Connection* connection);
    ~LobbyDialog();

    virtual void create( wxCommandEvent& event );
    virtual void join( wxCommandEvent& event );
    void OnTimer(wxTimerEvent& event);

    void recv();
};

#endif //CARCASONNE_LOBBYDIALOG_H
