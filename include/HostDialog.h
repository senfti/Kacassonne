//
// Created by ts on 29.03.20.
//

#ifndef CARCASONNE_HOSTDIALOG_H
#define CARCASONNE_HOSTDIALOG_H

#include <HostDialog_B.h>

class HostDialog : public HostDialog_B{
  protected:
    virtual void cancel( wxCommandEvent& event ) { EndModal(0); }
    virtual void start( wxCommandEvent& event ) { EndModal(1); }

};

#endif //CARCASONNE_HOSTDIALOG_H
