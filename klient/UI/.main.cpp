/*File "main.cpp" create by debial, (Вс 12 мар 2023 14:53:11)*/
#include "objects/Label/label.h"
#include "objects/ProgressBar/ProgressBar.h"
#include "objects/QtObject/ActionQtObject.h"
#include "screen/screen.h"
#include "objects/QtObject.h"
#include <curses.h>


void handler(Button *button){
   mvprintw(0, 0,"handler: %s",button->text);
}

class TestButton : public ButtonHandler{
   public:
   bool handler(Screen *screen){
      screen->set_action("b1");
      return true;
   }
};

int main(){
   initscr();
   setlocale(LC_ALL, "");
   start_color();
   noecho();
   keypad(stdscr,1);
   nodelay(stdscr, false);
   curs_set(0);
   Screen screen(stdscr,coord(COLS,LINES));
   Line line(coord(5,0),coord(10,5));
   BorderActionLabel label1(coord(5,0),coord(10,4),42,'*','#',"grish1");
   BorderActionLabel label2(coord(5,0),coord(10,4),42,'*','#',"grish2");
   BorderActionLabel label3(coord(5,0),coord(10,4),42,'*','#',"grish3");
   BorderActionLabel label4(coord(0,0),coord(10,10),42,'*','#',"prev list");
   BorderActionLabel label5(coord(30,0),coord(10,10),42,'*','#',"post list");
   EditLabel elabel(coord(25,0),coord(10,10),42,'*','#'," ");

   Button button1(&label1,'f',handler);
   Button button2(&label2,'f',handler);
   Button button3(&label3,'f',handler);
   Button button4(&label4,'f',handler);
   Button button5(&label5,'f',handler);
   QtList list(coord(13,0),coord(15,15),0);
   
   button4.set_action(&list, RightDirection);
   button5.set_action(&list, LeftDirection);

   list.add(&button1);
   list.add(&button2);
   list.add(&button3);
   list.add(&elabel);
   
   MemoryInfo bar(coord(1,40),coord(10,4));
   bar.set_percent(50);
   screen.add("bar",&bar,0);
   screen.add_button(266,new TestButton);
   screen.add_action("b1",&button4,0);
   screen.add_action("b2",&button5,0);
   screen.add("list",&list,0);
   timespec time={0,30000000};
   //cchar_t c;
   //setcchar(&c,L"\u2588" , 0, 0, NULL); 
   //mvadd_wch(30,30,&c);
   //refresh();
   screen.render();
   while(1){
      int input=getch();
      if(input=='q') break;
      clear();
      screen.handler(input);
      screen.render();
      refresh();
      nanosleep(&time,0);
   }
   endwin();
}
