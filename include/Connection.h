//
// Created by ts on 29.03.20.
//

#ifndef CARCASONNE_CONNECTION_H
#define CARCASONNE_CONNECTION_H

#include <wx/memory.h>
#include <wx/wx.h>
#include <mutex>
#include "Message.h"

enum class GameStatus { OPEN=0, STARTED=1, FINiSHED=2};

class Connection{
  public:
    std::mutex send_lock_;

    zmq::context_t context_;
    zmq::socket_t sub_;
    zmq::socket_t pub_;
    std::string player_name_;
    long player_id_ = getID();
    std::string game_name_;
    long game_id_ = 0;
    int game_status = 0;
    std::vector<std::pair<long, std::string>> players_;
    int player_number_ = -1;
    long host_ = 0;
    bool ok_ = false;

    Connection(const wxString& ip, const wxString& pub_port, const wxString& sub_port, const wxString& player_name);

    long send(const std::string& topic, Message msg);
    bool fromMe(const Message& msg) const { return msg["player_id"].get<long>() == player_id_; }
    bool forMe(const Message& msg) const;
    bool iAmHost() const { return host_ == player_id_; }
    bool fromHost(const Message& msg) const { return msg["host"].get<long>() == msg["player_id"].get<long>(); }
    std::pair<std::string, Message> recv();
};

#endif //CARCASONNE_CONNECTION_H
