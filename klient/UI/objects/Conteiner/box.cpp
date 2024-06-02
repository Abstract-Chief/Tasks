/*File "box.cpp" create by debial, (Сб 15 апр 2023 21:41:27)*/
#include "box.h"
#include <exception>
int KeyMovingArr[4]={KEY_UP,KEY_RIGHT,KEY_DOWN,KEY_LEFT};
ActionQtObject *ActionQtBox::move(int input){
   int direction=-1;
   for(int i=0;i<4;i++) 
      if(KeyMovingArr[i]==input) direction=i;
   if(direction==-1) return NULL;
   if(special[direction].count(current)==0){
      current->select(false);
      if(current->map[direction]!=NULL)
         current=current->map[direction];
      current->select(true);
      return NULL;
   }
   return map[direction];
   
}
void ActionQtBox::add_special(ActionQtObject *obj,Direction dir){
   if(current==NULL) current=obj;
   special[dir-1].insert(obj);    
}
