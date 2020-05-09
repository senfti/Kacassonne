//
// Created by ts on 09.05.20.
//

#ifndef KACASSONNE_RECONNECTDIALOG_H
#define KACASSONNE_RECONNECTDIALOG_H

#include "ReconnectDialog_B.h"
#include <fstream>

class ReconnectDialog : public ReconnectDialog_B{
  public:
    int64_t game_id_ = 0;
    int64_t player_id_ = 0;

    ReconnectDialog();

    virtual void cancel( wxCommandEvent& event ) { game_id_ = -1; player_id_ = 0; EndModal(-1); }
    virtual void connect( wxCommandEvent& event );
};

#endif //KACASSONNE_RECONNECTDIALOG_H
