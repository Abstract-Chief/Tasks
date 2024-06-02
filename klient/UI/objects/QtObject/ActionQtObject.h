/*File "ActionQtObject.cpp" create by debial, (Сб 11 мар 2023 16:56:26)*/
#ifndef DEBIAL_ACTIONQTOBJECT_H_SENTURY
#define DEBIAL_ACTIONQTOBJECT_H_SENTURY

//up=1 | down=2 | left=3 | right=4
#include "object.h"
#include <err.h>
#include <stdio.h>
#include <unistd.h>

enum Direction{
   UpDirection=1,
   RightDirection=2,
   DownDirection=3,
   LeftDirection=4,
};
class ActionQtObject{
   public:
   ActionQtObject *map[4];
   QtObject *graphick;
   virtual int MyHandler(int input) = 0;
   virtual void select(bool type) = 0;
   inline ActionQtObject *handler(int input){
      if(input==KEY_UP || input==KEY_DOWN || input==KEY_LEFT || input==KEY_RIGHT)
         return move(input);
      int res=MyHandler(input);
      if(res!=0) err(1,"trouble in handler");
      return NULL;
   }
   ActionQtObject(QtObject *obj);
   virtual ~ActionQtObject(){}
   virtual ActionQtObject* move(int input);
   void set_action(ActionQtObject *,Direction direction,bool reverse=true);
};



#endif
