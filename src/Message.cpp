//
// Created by senfth on 17.10.18.
//

#include <iostream>
#include <iomanip>
#include <chrono>

#include "Message.h"

int64_t getID(){
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

Message Message::fromJsonString(const std::string &msg){
  try{
    return Message(nlohmann::json::parse(msg.begin(), msg.begin() + msg.rfind("}") + 1));
  }
  catch(std::exception &e){
    std::cout << e.what() << std::endl;
  }
  return Message("");
}

std::pair<std::string, Message> Message::fromSocket(zmq::socket_t &sub){
  zmq::message_t topic_msg;
  std::string msg, topic;
  int64_t more;
  size_t more_size = sizeof more;

  bool success = sub.recv(&topic_msg);
  topic = std::string(static_cast<const char *>(topic_msg.data()), topic_msg.size());
  if((!success && errno == EAGAIN) || topic.empty()){
    return std::pair<std::string, Message>("", Message(std::string()));
  } else if(!success){
    std::cout << "Error while receiving message: Errno=" << errno << std::endl;
    return std::pair<std::string, Message>("", Message(std::string()));
  }
  sub.getsockopt(ZMQ_RCVMORE, &more, &more_size);
  while(more){
    /* Create an empty ØMQ message to hold the message part */
    zmq::message_t part;
    sub.recv(&part, 0);
    sub.getsockopt(ZMQ_RCVMORE, &more, &more_size);
    msg += std::string(static_cast<const char *>(part.data()), part.size());
  }

  return std::pair<std::string, Message>(topic, fromJsonString(msg));
}

Message::Message(const nlohmann::json &msg)
  : nlohmann::json(msg){
}

std::string Message::toJsonString() const{
  return dump(-1, ' ', true);
}

void Message::toSocket(zmq::socket_t &pub, const std::string &topic) const{
  zmq::message_t msg(topic.c_str(), topic.size());
  pub.send(msg, ZMQ_SNDMORE);
  std::string str = toJsonString();
  msg = zmq::message_t(str.c_str(), str.size());
  pub.send(msg, 0);
}
