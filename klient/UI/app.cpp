/*File "app.cpp" create by debial, (Пн 24 апр 2023 17:58:46)*/
#include "app.h"
#include "objects/Label/label.h"
#include <curses.h>
#include<signal.h>

Screen *CurrentScreen=NULL;

//void resize_signal_handler(int sig){
   //if(CurrentScreen==NULL) return;
   ////clear();
   ////CurrentScreen->render();
   ////refresh();
//}
GraphickApp::GraphickApp(){
   initscr();
   struct sigaction sa;
       sa.sa_handler = NULL;
       sigemptyset(&sa.sa_mask);
       sa.sa_flags = 0;
       sigaction(SIGWINCH, &sa, NULL);
   setlocale(LC_ALL, "");
   use_default_colors();
   start_color();
   noecho();
   keypad(stdscr,1);
   nodelay(stdscr, false);
   curs_set(0);
   init_pair(PassiveColor,-1,-2);
   init_pair(ActionColor,COLOR_RED,-2);
   init_pair(ChooseColor,COLOR_GREEN,-2);
}
GraphickApp::~GraphickApp(){
   endwin();
}
void GraphickApp::add(int id,Screen *screen){
   screens.insert(std::make_pair(id,screen));
   if(current==NULL) CurrentScreen=current=screen;
}
void GraphickApp::del(int id){
   screens.erase(id);
}
void GraphickApp::set(int id){
   CurrentScreen=current=screens.at(id);
}
Screen *GraphickApp::get(int id){
   return screens.at(id);
}
