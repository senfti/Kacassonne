//
// Created by ts on 29.03.20.
//

#include "Connection.h"

Connection::Connection(const wxString &ip, const wxString &pub_port, const wxString &sub_port, const wxString& player_name)
  :context_(1), sub_(context_, ZMQ_SUB), pub_(context_, ZMQ_PUB), player_name_(player_name)
{
  sub_.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  sub_.setsockopt(ZMQ_RCVTIMEO, 1000);
  sub_.connect("tcp://" + ip + ":" + sub_port);
  pub_.connect("tcp://" + ip + ":" + pub_port);
  wxMilliSleep(1000);

  Message msg;
  long id = send("ping", msg);
  while(true){
    auto [t, m] = recv();
    try{
      if(t == "ping" && m["id"].get<long>() == id){
        ok_ = true;
        return;
      }
      if(getID() - id > 3e9){
        return;
      }
    }
    catch(std::exception& e){
      std::cout << e.what() << std::endl;
    }
  }
}

bool Connection::forMe(const Message& msg) const {
  return (game_id_ == 0 || msg["game_id"].get<long>() == game_id_);
}

long Connection::send(const std::string& topic, Message msg){
  msg["game_name"] = game_name_;
  msg["game_id"] = game_id_;
  msg["player_number"] = player_number_;
  msg["player_name"] = player_name_;
  msg["player_id"] = player_id_;
  msg["players"] = players_;
  long id = getID();
  msg["id"] = id;
  msg["game_status"] = game_status;
  msg["host"] = host_;
  std::cout << "send: " << topic << " " << msg << std::endl;
  std::lock_guard<std::mutex> lock(send_lock_);
  msg.toSocket(pub_, topic);
  return id;
}

std::pair<std::string, Message> Connection::recv(){
  auto [t, m] = Message::fromSocket(sub_);
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
  std::cout << "recv: " << t << " " << m << std::endl;
  return std::make_pair(t, m);
}
