/* button.cpp" create by debial, (Вс 12 мар 2023 18:29:45)*/
#include "button.h"
#include <curses.h>
Button::Button(ActionLabel* label,char button_,ButtonHandler *handler_)
   : ActionQtObject(label),button(button_),handler(handler_),text(label->get_text()){
}
int Button::MyHandler(int input){
   mvprintw(0,0,"try use button");
   if(input==button) handler->handler(this);
   return 0;
}
void Button::select(bool type){
   if(type)
      ((ActionLabel*)graphick)->active();
   else
      ((ActionLabel*)graphick)->disactive();
}
