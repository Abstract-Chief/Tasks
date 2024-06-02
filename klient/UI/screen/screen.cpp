/*File "screen.cpp" create by debial, (Пт 10 мар 2023 14:38:57)*/
#include "screen.h"
#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
//сделать ресайз в графике

void CloseSignalHandler(int s){
   endwin();
   switch (s) {
      case SIGBUS: printf("get death(seagmentation fault)\n");
   }
   printf("succeful close from signal %d\n",s);
   exit(1);
}

void set_close_signal(){
   int signals[]={SIGINT,SIGBUS,SIGFPE,SIGTERM,SIGKILL};
   for(int i=0;i<(int)sizeof(signals);i++)
      signal(signals[i],CloseSignalHandler);
}

void Screen::rendering(float x_res,float y_res){
   for(auto it=storage.begin();it!=storage.end();it++)
      it->second->obj->graphick(x_res,y_res);
}
void Screen::Arendering(float x_res,float y_res){
   for(auto it=ActionStorage.begin();it!=ActionStorage.end();it++)
      it->second->obj->graphick->graphick(x_res,y_res);
}
void Screen::DebugGraphick(){
   if(debug==2 && size==coord(getmaxx(window),getmaxy(window))) return;
   debug=2;
   box(window,0,0);
   mvprintw(window->_begy-2,window->_begx,"count object: %d\n",count);
   refresh();
}
Screen::Screen(WINDOW *win,coord base_size,bool debug_) 
   : window(win),action(NULL),size(base_size),debug(debug_),count(0),ActionCount(0){
      set_close_signal();
      cbreak();
      if(!debug) return;
      printf("debug = %d\n",debug);
      mvwin(window,window->_begy+3,window->_begx+3);
   }
Screen::Screen() 
   : window(stdscr),action(NULL),size(COLS,LINES),debug(false),count(0),ActionCount(0){
      set_close_signal();
      cbreak();
   }
Screen::~Screen(){
   
   for(auto it=storage.begin();it!=storage.end();it++){
      if(it->second->type)
         delete it->second->obj;
      delete it->second;
   }
   for(auto it=ButtonStorage.begin();it!=ButtonStorage.end();it++)
         delete it->second;
   for(auto it=ActionStorage.begin();it!=ActionStorage.end();it++){
      if(it->second->type)
         delete it->second->obj;
      delete it->second;
   }
}
void Screen::add(int name,QtObject *object,bool del){
   if(name==0)
      storage.insert(std::make_pair(0,new Block(object,del)));
   else if(storage.count(name)==0){
      storage.insert(std::make_pair(name,new Block(object,del)));
   }
   else err(1,"error: try dublicate %d",name);
   object->set_window(window);
   count++;
};
void Screen::add_action(int name,ActionQtObject *object,bool del){
   if(name==-1)
      ActionStorage.insert(std::make_pair(0,new ABlock(object,del)));
   else if(ActionStorage.count(name)==0)
      ActionStorage.insert(std::make_pair(name,new ABlock(object,del)));
   else err(1,"error: try dublicate %d",name);
   object->graphick->set_window(window);
   ActionCount++;
   if(action==NULL) action=object;
}
void Screen::add_button(int key,KeyHandler *object){
   if(ButtonStorage.count(key)==0)
      ButtonStorage.insert(std::make_pair(key,object));
   else err(1,"error: try dublicate button handler %d\n",key);
   ActionCount++;
}
void Screen::render(){
   struct winsize ws;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
   coord s_size={(short)ws.ws_col,(short)ws.ws_row};
   double x_res,y_res;
   x_res=(double)s_size.x/(double)size.x;
   y_res=(double)s_size.y/(double)size.y;
   rendering(x_res,y_res);
   Arendering(x_res,y_res);
   if(debug) DebugGraphick();
   wnoutrefresh (window);
   doupdate();
}
void Screen::set_action(int name){
   if(action!=NULL)
      action->select(false);
   action=ActionStorage.at(name)->obj;
   action->select(true);
}

ActionQtObject *Screen::get_action(int name){
   return ActionStorage.at(name)->obj;
}
QtObject *Screen::get(int name){
   return storage.at(name)->obj;
}

