//
// Created by ts on 09.05.20.
//

#ifndef KACASSONNE_SHOWIDSDIALOG_H
#define KACASSONNE_SHOWIDSDIALOG_H

#include "IdsDialog_B.h"
#include "Connection.h"

class IdsDialog : public IdsDialog_B{
  public:
    IdsDialog(wxWindow* parent, const Connection* connection)
      : IdsDialog_B(parent)
    {
      std::string text = "Game ID: " + std::to_string(connection->game_id_);
      for(const auto& p : connection->players_){
        text += "\n" + p.name_ + ": " + std::to_string(p.id_);
      }
      ids_text_->SetValue(text);
    }
};

#endif //KACASSONNE_SHOWIDSDIALOG_H
