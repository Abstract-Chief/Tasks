/*File "main.cpp" create by debial, (Вс 12 мар 2023 14:53:11)*/
#include "objects/Label/label.h"
#include "objects/ProgressBar/ProgressBar.h"
#include "objects/tasks/TaskObject.h"
#include "objects/QtObject/ActionQtObject.h"
#include "objects/Conteiner/box.h"
#include "screen/screen.h"
#include "objects/QtObject.h"
#include "objects/Notice/notice.h"
#include "objects/Conteiner/list.h"
#include "app.h"
#include <curses.h>
#include "../../procs/parser.h"

void handler(Button *button){
   mvprintw(0, 0,"handler: %s",button->text);
}
//rofl
int main(){

   GraphickApp app;
   Screen screen(stdscr,coord(COLS,LINES));
   QtList list(coord(5,5),coord(20,5),1,NULL);
   list.add(new Label(coord(0,0),coord(20,0),20,"grisha"));
   list.add(new Label(coord(0,0),coord(20,0),20,"grisha"));
   list.add(new Label(coord(0,0),coord(20,0),20,"grisha"));
   list.add(new Label(coord(0,0),coord(20,0),20,"grisha"));
   list.add(new Label(coord(0,0),coord(20,0),20,"grisha"));
   list.add(new Label(coord(0,0),coord(20,0),20,"grisha"));
   list.add(new Label(coord(0,0),coord(20,0),20,"grisha"));
   list.add(new Label(coord(0,0),coord(20,0),20,"grisha"));
   screen.add_action(5,&list,false);
   screen.set_action(5);
   list.select(true);
   refresh();
   timespec time={0,30000000};
   while(1){
      int input=getch();
      if(input=='q') break;
      clear();
      screen.handler(input);
      screen.render();
      refresh();
      nanosleep(&time,0);
   }
}
