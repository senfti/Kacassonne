#include <GameDialog.h>
#include <csignal>

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
  ConnectDialog* cd = new ConnectDialog();
  cd->ShowModal();
  connection_ = new Connection(cd->ip_, cd->pub_port_, cd->sub_port_, cd->name_);
  delete cd;
  if(!connection_->ok_){
    wxMessageBox("Connection Failed!");
    return false;
  }
  LobbyDialog* ld = new LobbyDialog(connection_);
  if(ld->ShowModal() != 0)
    return false;
  delete ld;

  GameDialog* gd = new GameDialog(connection_);
  if(gd->ShowModal() != 0)
    return false;
  int card_number = gd->card_number_;
  delete gd;
  connection_->subscribeToGame();

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

  return true;
}

bool MyApp::reset(){
  main_frame_->Hide();
  int card_number = game_->getLeftCards() + game_->played_cards_.size();
  delete game_;
  game_ = new Game(connection_, card_number);
  main_frame_->setGame(game_, true);
  main_frame_->Show();

  return true;
}

int MyApp::OnExit(){
  return 0;
}