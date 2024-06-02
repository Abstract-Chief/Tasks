/*File "input_conf.h" create by debial, (Пн 24 апр 2023 17:50:58)*/
#ifndef DEBIAL_INPUT_CONF_H_SENTURY
#define DEBIAL_INPUT_CONF_H_SENTURY
#include"../UI/app.h"
#include "../module/BaseKlient.h"
class MyInputHandler : public InputHandler{
   GraphickApp *app;
   public:
   MyInputHandler(GraphickApp *app_) : app(app_){}
   void handler(){
      int input=getch();
      if(input!=KEY_RESIZE)
         app->current->handler(input);
      else
         app->current->render();
   }
};


#endif
