#include <GameDialog.h>
#include <csignal>
#include <filesystem>

#include "main.h"
#include "ConnectDialog.h"
#include "Connection.h"
#include <LobbyDialog.h>

#ifdef __linux__
#include <execinfo.h>
#include <cxxabi.h>
#endif

MyApp* my_app;
IMPLEMENT_APP(MyApp)

void signal_handler(int signal)
{
  std::ofstream f("crash_log.txt");
  f << "Signal " << (signal == SIGFPE ? "SIGFPE" : "SIGSEGV") << std::endl;
  std::cout << "Signal " << (signal == SIGFPE ? "SIGFPE" : "SIGSEGV") << std::endl;
#ifdef __linux__
  void *array[50];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 50);
  char **ptr = backtrace_symbols(array, size);
  for(unsigned i=0; i<size; i++){
    bool found_bracket = false;
    char* c = ptr[i];
    while(*c != '\0'){
      if(*c == '(')
        found_bracket = true;
      else if(*c == '_' && found_bracket)
        break;
      c++;
    }
    if(*c == '\0')
      continue;
    char* c2 = c;
    while(*c2 != '\0'){
      if(*c2 == '+'){
        *c2 = '\0';
      }
      c2++;
    }
    if(*(c+1) == 'Z'){
      int status = -1;
      char *demangledName = abi::__cxa_demangle(c, NULL, NULL, &status);
      if(status == 0){
        f << demangledName << std::endl;
        std::cout << demangledName << std::endl;
      }
      free(demangledName);
    }
    else{
      f << c << std::endl;
      std::cout << c << std::endl;
    }
  }
  free(ptr);
#endif
  exit(1);
}


bool MyApp::OnInit(){
  std::signal(SIGSEGV, signal_handler);
  std::signal(SIGFPE, signal_handler);
  my_app = this;
  if(std::filesystem::exists("settings.txt")){
    std::ifstream f("settings.txt");
    std::string ip, pub_port, sub_port, name;
    try{
      std::getline(f, ip);
      std::getline(f, pub_port);
      std::getline(f, sub_port);
      std::getline(f, name);
      if(!name.empty())
        connection_ = new Connection(ip, pub_port, sub_port, name);
      else
        wxMessageBox("Invalid settings file");
    }
    catch(std::exception&){
      wxMessageBox("Invalid settings file");
    }
  }
  if(connection_ == nullptr || !connection_->ok_){
    ConnectDialog *cd = new ConnectDialog();
    cd->ShowModal();
    connection_ = new Connection(cd->ip_, cd->pub_port_, cd->sub_port_, cd->name_);
    delete cd;
  }
  if(!connection_->ok_){
    wxMessageBox("Connection Failed!");
    return false;
  }

  int card_number = lobbyStuff();
  if(card_number < 0)
    return false;

  return initGame(card_number);
}

int MyApp::lobbyStuff(){
  LobbyDialog* ld = new LobbyDialog(connection_);
  if(ld->ShowModal() != 0)
    return -1;
  delete ld;

  GameDialog* gd = new GameDialog(connection_);
  if(gd->ShowModal() != 0)
    return -1;

  int card_number = gd->card_number_;
  delete gd;
  connection_->subscribeToGame();

  return card_number;
}

bool MyApp::initGame(int card_number){
  MainFrame* tmp = main_frame_;
  delete game_;
  game_ = nullptr;
  wxMilliSleep(1500);

  try{
    game_ = new Game(connection_, card_number);
    if(game_->stack_.getLeftCards() < 1){
      wxMessageBox("Failed loading card images!");
      return false;
    }
    main_frame_ = new MainFrame(this);
  }
  catch (std::bad_alloc& exception){
    wxMessageBox("Not enough memory!", "Fatal Error", wxICON_ERROR);
    return false;
  }
  catch(std::exception& e){
    std::cout << e.what() << std::endl;
    return false;
  }

//  main_frame_->SetTitle(connection_->player_name_);
  main_frame_->setGame(game_);
  main_frame_->Show();

  if(tmp)
    tmp->Destroy();

  return true;
}

bool MyApp::reset(bool to_lobby){
  main_frame_->disable();
  main_frame_->Hide();
  int card_number = game_->getLeftCards() + game_->played_cards_.size();
  if(to_lobby){
    delete game_;
    game_ = nullptr;
    Connection* tmp = connection_;
    connection_ = new Connection(tmp->ip_, tmp->pub_port_, tmp->sub_port_, tmp->player_name_);

    card_number = lobbyStuff();
    if(card_number < 0)
      return false;
  }

  return initGame(card_number);
}

int MyApp::OnExit(){
  return 0;
}