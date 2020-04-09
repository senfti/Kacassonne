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
    std::string sub_topic_ = "lobby";

    std::ofstream log_file = std::ofstream("message_log.txt", std::ios::app | std::ios::out);

    std::string player_name_;
    int64_t player_id_ = getID();
    std::string game_name_;
    int64_t game_id_ = 0;
    int game_status = 0;
    std::vector<std::pair<int64_t, std::string>> players_;
    int player_number_ = -1;
    int64_t host_ = 0;
    bool ok_ = false;

    Connection(const wxString& ip, const wxString& pub_port, const wxString& sub_port, const wxString& player_name);

    void subscribeToGame();

    int64_t send(const std::string& topic, Message msg);
    bool fromMe(const Message& msg) const { return msg["player_id"].get<int64_t>() == player_id_; }
    bool forMe(const Message& msg) const;
    bool iAmHost() const { return host_ == player_id_; }
    bool fromHost(const Message& msg) const { return msg["host"].get<int64_t>() == msg["player_id"].get<int64_t>(); }
    std::pair<std::string, Message> recv();
};

#endif //CARCASONNE_CONNECTION_H
