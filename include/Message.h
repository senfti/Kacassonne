//
// Created by ts on 29.03.20.
//

#ifndef CARCASONNE_MESSAGE_H
#define CARCASONNE_MESSAGE_H

#include <zmq.hpp>
#include <fstream>
#include "nlohmann/json.hpp"
#include <chrono>


int64_t getID();
double getTime();

// nlohmann::json is not made for inheritance, so use with care
class Message : public nlohmann::json{
  public:
    static Message fromJsonString(const std::string& msg);
    static std::pair<std::string, Message> fromSocket(zmq::socket_t& sub);

    Message() {}
    Message(const nlohmann::json& msg);
    std::string toJsonString() const;
    void toSocket(zmq::socket_t& pub, const std::string& topic) const;
};

#endif //CARCASONNE_MESSAGE_H
