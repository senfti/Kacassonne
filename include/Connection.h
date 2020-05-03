//
// Created by ts on 29.03.20.
//

#ifndef CARCASONNE_CONNECTION_H
#define CARCASONNE_CONNECTION_H

#include <wx/memory.h>
#include <wx/wx.h>
#include <mutex>
#include "Message.h"

enum class GameStatus { OPEN=0, STARTED=1, FINISHED=2};

struct PlayerCon{
  int64_t id_ = 0;
  std::string name_ = "";
  size_t color_ = 0;

  PlayerCon() {}
  PlayerCon(int64_t id, const std::string& name, size_t color) : id_(id), name_(name), color_(color) {}
  PlayerCon(const PlayerCon& p) : id_(p.id_), name_(p.name_), color_(p.color_) {}

  friend void to_json(nlohmann::json& j, const PlayerCon& p) {
    j = nlohmann::json{{"id", p.id_}, {"name", p.name_}, {"color", p.color_}};
  }
  friend void from_json(const nlohmann::json& j, PlayerCon& p) {
    j.at("id").get_to(p.id_);
    j.at("name").get_to(p.name_);
    j.at("color").get_to(p.color_);
  }
};

class Connection{
  public:
    std::mutex send_lock_;

    zmq::context_t context_;
    zmq::socket_t sub_;
    zmq::socket_t pub_;
    std::string sub_topic_ = "lobby";
    wxString ip_;
    wxString pub_port_;
    wxString sub_port_;

//    std::ofstream log_file = std::ofstream("message_log.txt", std::ios::app | std::ios::out);

    std::string player_name_;
    int64_t player_id_ = getID();
    std::string game_name_;
    int64_t game_id_ = 0;
    int game_status_ = 0;
    std::vector<PlayerCon> players_;
    int player_number_ = -1;
    int64_t host_ = 0;
    bool ok_ = false;

    Connection(const wxString& ip, const wxString& pub_port, const wxString& sub_port, const wxString& player_name);

    void subscribeToGame();
    void subscribeToLobby();

    int64_t send(const std::string& topic, Message msg);
    bool fromMe(const Message& msg) const { return msg["player_id"].get<int64_t>() == player_id_; }
    bool forMe(const Message& msg) const;
    bool iAmHost() const { return host_ == player_id_; }
    bool fromHost(const Message& msg) const { return msg["host"].get<int64_t>() == msg["player_id"].get<int64_t>(); }
    std::pair<std::string, Message> recv();
};

#endif //CARCASONNE_CONNECTION_H
