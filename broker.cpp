//
// Created by ts on 12.04.20.
//

#include <zmq.hpp>
#include <Message.h>

int main(){
  zmq::context_t context_(1);
  zmq::socket_t sub_(context_, ZMQ_SUB);
  zmq::socket_t pub_(context_, ZMQ_PUB);

  sub_.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  sub_.bind("tcp://127.0.0.1:10100");
  pub_.bind("tcp://127.0.0.1:10200");
  
  while(true){
    auto [t, m] = Message::fromSocket(sub_);
    m.toSocket(pub_, t);
  }
}

