/*File "ActionQtObject.cpp" create by debial, (Сб 11 мар 2023 16:56:28)*/
#include "ActionQtObject.h"
#include "object.h"
//inline ActionQtObject* ActionQtObject::handler(char input){
//}
ActionQtObject::ActionQtObject(QtObject *obj) : graphick(obj){
   map[0]=NULL;
   map[1]=NULL;
   map[2]=NULL;
   map[3]=NULL;
}

void ActionQtObject::set_action(ActionQtObject *obj,Direction direction,bool rev){
   if(direction<=4 && direction>0)
      map[direction-1]=obj;
   if(rev){
      if(direction==UpDirection) map[direction-1]->set_action(this,DownDirection,false);
      if(direction==DownDirection) map[direction-1]->set_action(this,UpDirection,false);
      if(direction==RightDirection) map[direction-1]->set_action(this,LeftDirection,false);
      if(direction==LeftDirection) map[direction-1]->set_action(this,RightDirection,false);
   }
}
ActionQtObject* ActionQtObject::move(int input){
   if(input==KEY_UP)
      return map[UpDirection-1];
   else if(input==KEY_DOWN)
      return map[DownDirection-1];
   else if(input==KEY_LEFT)
      return map[LeftDirection-1];
   else if(input==KEY_RIGHT)
      return map[RightDirection-1];
   return NULL;
}
