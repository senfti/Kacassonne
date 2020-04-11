//
// Created by ts on 28.03.20.
//

#include <Stack.h>
#include <algorithm>
#include <random>

Stack::Stack(unsigned card_number){
  if(!Card::initCardImages())
    return;

  std::vector<Card> tmp;
  for(unsigned c=0; c<Card::CARD_IMAGES.size(); c++){
    for(int i=0; i<Card::CARD_IMAGES[c].second; i++)
      tmp.push_back(Card(c));
  }
  while(tmp.size() < card_number)
    tmp.insert(tmp.end(), tmp.begin(), tmp.end());

  std::mt19937 eng(time(0));
  std::shuffle(std::next(tmp.begin(), 1), tmp.end(), eng);
  cards_ = std::list<Card>(tmp.begin(), tmp.begin() + card_number);
}

void Stack::shuffle(){
  std::vector<Card> tmp;
  for(const auto& c : cards_)
      tmp.push_back(c);
  std::mt19937 eng(time(0));
  std::shuffle(tmp.begin(), tmp.end(), eng);
  cards_ = std::list<Card>(tmp.begin(), tmp.end());
}

Card* Stack::next(){
  if(cards_.empty())
    return nullptr;
  return &*cards_.begin();
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
