//
// Created by ts on 28.03.20.
//

#include <Stack.h>
#include <algorithm>
#include <random>

Stack::Stack(unsigned card_number, const std::map<std::string, int>& card_count){
  if(!Card::initCardImages())
    return;

  if(card_number < 0){
    cards_ = {Card(0)};
    return;
  }

  std::vector<Card> deck, used_cards;
  for(unsigned c=0; c<Card::CARD_IMAGES.size(); c++){
    int cnt = (card_count.find(Card::CARD_IMAGES[c].name_) != card_count.end() ? card_count.at(Card::CARD_IMAGES[c].name_) : 0);
    for(int i=0; i<cnt; i++)
      deck.push_back(Card(c));
  }

  if(deck.size() < 1)
    return;

  std::mt19937 eng(time(0));
  while(used_cards.size() < card_number) {
    if(card_number - used_cards.size() >= deck.size())
      used_cards.insert(used_cards.end(), deck.begin(), deck.end());
    else{
      std::shuffle(card_number > deck.size() ? deck.begin() : std::next(deck.begin(), 1), deck.end(), eng);
      std::random_device eng2;
      std::shuffle(card_number > deck.size() ? deck.begin() : std::next(deck.begin(), 1), deck.end(), eng2);
      used_cards.insert(used_cards.end(), deck.begin(), std::next(deck.begin(), card_number - used_cards.size()));
    }
      
  }
  std::shuffle(std::next(used_cards.begin(), 1), used_cards.end(), eng);
  std::random_device eng2;
  std::shuffle(std::next(used_cards.begin(), 1), used_cards.end(), eng2);
  cards_ = std::list<Card>(used_cards.begin(), used_cards.end());
}

void Stack::shuffle(){
  std::vector<Card> tmp;
  for(const auto& c : cards_)
      tmp.push_back(c);
  std::mt19937 eng(time(0));
  std::shuffle(tmp.begin(), tmp.end(), eng);
  cards_ = std::list<Card>(tmp.begin(), tmp.end());
}

Card* Stack::next() {
  if(cards_.empty())
    return nullptr;
  return &*cards_.begin();
}


Card* Stack::next(unsigned n) {
  if(cards_.size() < n)
    return nullptr;
  return &*std::next(cards_.begin(), n);
}


void Stack::pop(){
  cards_.pop_front();
}


Card Stack::get(){
  if(cards_.empty())
    return Card(-1);
  Card c = cards_.front();
  cards_.pop_front();
  return c;
}


void Stack::push(const Card& card){
  cards_.push_front(card);
}
