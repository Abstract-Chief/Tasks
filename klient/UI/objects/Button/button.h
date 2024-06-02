/*File "button.cpp" create by debial, (Вс 12 мар 2023 18:29:46)*/
#ifndef DEBIAL_BUTTONF_H_SENTURY
#define DEBIAL_BUTTONF_H_SENTURY

#include"../QtObject/ActionQtObject.h"
#include "../Label/label.h"
class Button;
class ButtonHandler{
   public:
   virtual int handler(Button *button)=0;
};

class Button : public ActionQtObject{
   char button;
   public:
   ButtonHandler *handler;
   const char *text;
   Button(ActionLabel *label,char button,ButtonHandler *handler_);
   void set_handler(ButtonHandler *handler_){
      handler=handler_;
   }
   int MyHandler(int input);
   void select(bool type);
};

#endif
