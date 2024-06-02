/*File "list.cpp" create by debial, (Вс 12 мар 2023 21:00:02)*/
#include "list.h"
#include "box.h"
#include <curses.h>

extern int KeyMovingArr[4];
QtList::QtList(coord pos,coord size,int heigh_,QtObjectHandler *handler_,int acolor_,int pcolor_) 
   : ActionQtObject(this),QtObject(pos,size),handler(handler_),backcur(-1),current(-1),heigh(heigh_),acolor(acolor_),pcolor(pcolor_){}
QtList::~QtList(){}
void QtList::select(bool type){
   if(type){
      if(current==-1 && (int)labels.size()!=0) current=0;
      else current=backcur;
   }else current=-1;
}
void QtList::add(QtObject *obj){
   labels.push_back(obj);
}

int QtList::MyHandler(int input){
   handler->handler(labels[current],input);
   return 0;
}
ActionQtObject *QtList::move(int input){
   mvprintw(1,0,"%d %d ",current,(int)labels.size()-1);
   if(input==KEY_DOWN){
      if(current==(int)labels.size()-1) return map[DownDirection-1];
      current++;
   }else if(input==KEY_UP){
      if(current<=0) return map[UpDirection-1];
      current--;
   }else if(input==KEY_LEFT)
      return map[LeftDirection-1];
   else if(input==KEY_RIGHT)
      return map[RightDirection-1];
   backcur=current;
   return NULL;
}
void QtList::graphick(float x_res,float y_res){
   coord r_size(size.x*x_res,size.y*y_res);
   coord r_pos(pos.x,pos.y);
   if(r_size.y<heigh) return;
   int N=r_size.y/heigh;
   int s=(current-N/2<0 ? 0 : current-N/2);
   int e=(s+N>=(int)labels.size() ? labels.size() : s+N);
   coord label_size(r_size.x,1);
   mvprintw(0,0,"%d %d %d ",current,s,e);
   for(int i=s;i<e;i++){
      if(i==current)
         labels[i]->coloron(COLOR_PAIR(acolor));
      labels[i]->set_pos(coord(r_pos.x,r_pos.y),label_size);
      labels[i]->graphick(x_res,y_res);
      if(i==current)
         labels[i]->coloroff(COLOR_PAIR(acolor));
      r_pos.y+=heigh;
   }
}

