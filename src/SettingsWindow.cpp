//
// Created by ts on 01.06.20.
//

#include <Card.h>
#include <wx/valnum.h>
#include <filesystem>
#include <fstream>
#include "SettingsWindow.h"


SettingsWindow::SettingsWindow(wxWindow* parent)
    : SettingsWindow_B(parent)
{
  all_card_counts_ = Card::loadCardCounts();
  all_card_counts_.insert({"custom", all_card_counts_["default"]});
  Card::initCardImages();
  int def_setting = 0;
  for(auto& setting : all_card_counts_){
    for(const auto ci : Card::CARD_IMAGES){
      if(setting.second.find(ci.name_) == setting.second.end())
        setting.second.insert({ci.name_, 0});
    }
    setting_choice_->Append(setting.first);
    if(setting.first == "default"){
      def_setting = int(setting_choice_->GetStrings().size()) - 1;
      current_count_ = setting.second;
    }
  }
  setting_choice_->SetSelection(def_setting);
  save_button_->Disable();

  std::vector<Card::CardImage> sorted_images = Card::CARD_IMAGES;
  std::sort(sorted_images.begin(), sorted_images.end());

  for(const auto ci : sorted_images){
    wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);
    wxStaticBitmap* bmp = new wxStaticBitmap(this, wxID_ANY, wxBitmap(ci.image_.Scale(80, 80)));
    s1->Add(bmp, 0, wxALL, 0);

    wxIntegerValidator<int> val(&current_count_[ci.name_]);
    val.SetMin(0);
    val.SetMax(99);
    count_textctrls_.insert({ci.name_, new wxTextCtrl(this, wxID_ANY, std::to_string(current_count_[ci.name_]), wxDefaultPosition, wxSize(80, -1))});
    count_textctrls_[ci.name_]->SetValidator(val);
    count_textctrls_[ci.name_]->Disable();

    s1->Add(count_textctrls_[ci.name_], 0, wxALL, 0);

    image_sizer_->Add(s1, 0, wxALL, 5);
  }
  this->Layout();
  this->Fit();
}

void SettingsWindow::changeSetting( wxCommandEvent& event ){
  balance_name_ = std::string(setting_choice_->GetString(setting_choice_->GetSelection()));
  for(auto& c : current_count_){
    c.second = all_card_counts_[balance_name_][c.first];
  }
  TransferDataToWindow();
  bool enable = balance_name_ == "custom";
  for(auto ctxt : count_textctrls_)
    ctxt.second->Enable(enable);
  save_button_->Enable(enable);
}

void SettingsWindow::save( wxCommandEvent& event ){
  std::string fn = std::string(Card::CARD_FOLDER + name_textctrl_->GetValue() + ".txt");
  if(name_textctrl_->GetValue() != "custom" && !std::filesystem::exists(fn)){
    TransferDataFromWindow();
    std::ofstream f(fn);
    for(const auto& c : current_count_){
      f << c.first << " " << c.second << std::endl;
    }
    f.close();
  }
}

void SettingsWindow::ok( wxCommandEvent& event ){
  TransferDataFromWindow();
  EndModal(0);
}
