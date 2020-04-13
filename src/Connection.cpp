//
// Created by ts on 29.03.20.
//

#include "Connection.h"

Connection::Connection(const wxString &ip, const wxString &pub_port, const wxString &sub_port, const wxString& player_name)
  :context_(1), sub_(context_, ZMQ_SUB), pub_(context_, ZMQ_PUB), player_name_(player_name)
{
  try{
    sub_.setsockopt(ZMQ_SUBSCRIBE, sub_topic_.c_str(), sub_topic_.size());
    sub_.setsockopt(ZMQ_RCVTIMEO, 1000);
    sub_.connect("tcp://" + ip + ":" + sub_port);
    pub_.connect("tcp://" + ip + ":" + pub_port);
  }
  catch(std::exception&){
    return;
  }
  wxMilliSleep(1000);

  Message msg;
  int64_t id = send("ping", msg);
  while(true){
    auto [t, m] = recv();
    try{
      if(t == "ping" && m["id"].get<int64_t>() == id){
        ok_ = true;
        return;
      }
      if(getID() - id > 1e10){
        return;
      }
    }
    catch(std::exception& e){
      std::cout << e.what() << std::endl;
    }
  }
}

void Connection::subscribeToGame(){
  sub_.setsockopt(ZMQ_UNSUBSCRIBE, sub_topic_.c_str(), sub_topic_.size());
  sub_topic_ = std::to_string(game_id_);
  sub_.setsockopt(ZMQ_SUBSCRIBE, sub_topic_.c_str(), sub_topic_.size());
}

bool Connection::forMe(const Message& msg) const {
  return (game_id_ == 0 || msg["game_id"].get<int64_t>() == game_id_);
}

int64_t Connection::send(const std::string& topic, Message msg){
  msg["game_name"] = game_name_;
  msg["game_id"] = game_id_;
  msg["player_number"] = player_number_;
  msg["player_name"] = player_name_;
  msg["player_id"] = player_id_;
  msg["players"] = players_;
  int64_t id = getID();
  msg["id"] = id;
  msg["game_status"] = game_status;
  msg["host"] = host_;
  msg["topic"] = topic;
  std::cout << "send: " << sub_topic_ << " " << msg << std::endl;
  log_file << "send: " << sub_topic_ << " " << msg << std::endl;
  std::lock_guard<std::mutex> lock(send_lock_);
  msg.toSocket(pub_, sub_topic_);
  return id;
}

std::pair<std::string, Message> Connection::recv(){
  auto [t, m] = Message::fromSocket(sub_);
  if(t == "" || m.find("topic") == m.end())
    return std::pair<std::string, Message>("", Message(std::string()));
  t = m["topic"];
  if(fromMe(m) && t != "ping")
    return std::pair<std::string, Message>("", Message(std::string()));
  if(t == "" || (fromMe(m) && t != "ping")){
    return std::pair<std::string, Message>("", Message(std::string()));
  }
  if(!forMe(m)){
    std::cout << "Not for me: " << t << " " << m << std::endl;
  }
  for(const auto& k : {"game_name", "game_id", "player_number", "player_name", "player_id", "id", "game_status", "host", "players"}){
    if(m.find(k) == m.end()){
      std::cout << "Invalid message: " << t << " " << m << std::endl;
      return std::pair<std::string, Message>("", Message(std::string()));
    }
  }
  log_file << "recv: " << sub_topic_ << " " << m << std::endl;
  std::cout << "recv: " << sub_topic_ << " " << m << std::endl;
  return std::make_pair(t, m);
}
