//
// Created by ts on 28.03.20.
//

#ifndef CARCASONNE_STACK_H
#define CARCASONNE_STACK_H

#include <list>
#include <string>
#include "Card.h"
#include "nlohmann/json.hpp"

class Stack{
  private:
    std::list<Card> cards_;

  public:
    Stack(unsigned card_number, const std::map<std::string, int>& card_count);
    Card* next();
    Card* next(unsigned n);
    void pop();
    Card get();
    void push(const Card& card);
    void shuffle();
    int getLeftCards() const { return cards_.size(); }
    const std::list<Card>& getAllCards() const { return cards_; }

    friend void to_json(nlohmann::json& j, const Stack& s) {
      j = nlohmann::json{{"cards", s.cards_}};
    }
    friend void from_json(const nlohmann::json& j, Stack& s) {
      j.at("cards").get_to(s.cards_);
    }
};

#endif //CARCASONNE_STACK_H
