//
// Created by ts on 28.03.20.
//

#include <Stack.h>
#include <algorithm>
#include <random>

Stack::Stack(){
  if(Card::CARD_IMAGES.empty())
    Card::initCardImages();

  std::vector<Card> tmp;
  for(int c=0; c<Card::CARD_IMAGES.size(); c++){
    for(int i=0; i<Card::CARD_IMAGES[c].second; i++)
      tmp.push_back(Card(c));
  }

  std::mt19937 eng(time(0));
  std::shuffle(std::next(tmp.begin(), 1), tmp.end(), eng);
  cards_ = std::list<Card>(tmp.begin(), tmp.end());
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
