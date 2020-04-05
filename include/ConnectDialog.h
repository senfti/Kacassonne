//
// Created by ts on 29.03.20.
//

#ifndef CARCASONNE_CONNECTDIALOG_H
#define CARCASONNE_CONNECTDIALOG_H

#include <ConnectDialog_B.h>

class ConnectDialog : public ConnectDialog_B{
  public:
    wxString ip_;
    wxString pub_port_;
    wxString sub_port_;
    wxString name_;

    ConnectDialog() : ConnectDialog_B(nullptr) { }

    virtual void connect( wxCommandEvent& event ) {
      ip_ = server_ip_textctrl_->GetValue();
      pub_port_ = pub_port_textctrl_->GetValue();
      sub_port_ = sub_port_textctrl_->GetValue();
      name_ = name_textctrl_->GetValue();
      EndModal(0);
    }
};

#endif //CARCASONNE_CONNECTDIALOG_H
