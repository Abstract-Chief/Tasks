/*File "list.cpp" create by debial, (Вс 12 мар 2023 21:00:02)*/
#include "list.h"
void QtList::setting_object(ActionQtObject *object){
   coord opos(0,0),osize(0,0);
   object->graphick->get_pos(&opos, &osize);
   osize.x=size.x-1;
   if(last==NULL) opos=coord(pos.x,pos.y);
   else opos=coord(pos.x,last->graphick->pos.y+last->graphick->size.y+space);
   object->graphick->set_pos(opos, osize);
}
QtList::QtList(coord pos,coord size,int space_) : ActionQtObject(this),QtObject(pos,size),a_ch(0),p_ch(0),space(space_),first(NULL),last(NULL){}
QtList::~QtList(){}
void QtList::select(bool type){
   if(first!=NULL)
   first->select(type);
}
void QtList::add(ActionQtObject *object){
   setting_object(object);
   if(first==NULL){
      last=first=object;
      object->set_action(map[LeftDirection-1],LeftDirection,true);
      object->set_action(map[RightDirection-1],RightDirection,true);
      return;
   }
   object->set_action(map[RightDirection-1],RightDirection,false);
   object->set_action(map[LeftDirection-1],LeftDirection,false);
   last->set_action(object,DownDirection);
   last=object;
}
void QtList::add_list(QtList *list){
   ActionQtObject *object=list->first;
   while(object!=NULL){
      add(object);
      object=object->map[DownDirection-1];
   }
}
int QtList::MyHandler(int input){
   return 0;
}
void QtList::graphick(float x_res,float y_res){
   ActionQtObject *object=first;
   while(object!=NULL){
      object->graphick->graphick(x_res,y_res);
      object=object->map[DownDirection-1];
   }
}

