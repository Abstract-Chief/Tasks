/*File "notice.cpp" create by debial, (Пн 17 апр 2023 22:30:21)*/
#include "notice.h"
QtNotice::QtNotice(coord pos,coord size,int heigh,int max_notice_) : QtObject(pos,size),max_notice(max_notice_),block_size(coord(size.x,heigh)){}
bool QtNotice::add(const char *text,int time,int color){
   if((int)notice.size()>=max_notice) return false;
   int len=strlen(text);
   if(len/(size.x-2)>=size.y) return false;
   if(len>128) return false;
   
   //char *text_copy=new char[len];
   //memcpy(text_copy,text,len);
   BorderActionLabel *label=new BorderActionLabel(coord(1,1),block_size,128,0,text,color,color);
   label->active();
   Notice *msg=new Notice;
   msg->label=label;msg->time=time;
   notice.push_front(msg);
   return true;  
}
void QtNotice::graphick(float x_res,float y_res){
   auto end=notice.end();
   int i=0;
   coord last(COLS-size.x*x_res-3,pos.y*y_res);
   for(auto it=notice.begin();it!=end;i++){
      Notice *msg=(*it);
      auto next=std::next(it);
      if(msg->time==1){
         notice.erase(it);
         delete msg->label;
         delete msg;
         it=next;
         continue;
      }
      coord bl_size_c=coord(block_size.x*x_res,block_size.y*y_res);
      //Rectangle *rect=&((BorderActionLabel*)msg->label)->rect;
      //rect->set_pos(last,rect->size);
      msg->label->set_pos(coord(0,0),coord(bl_size_c.x*x_res,bl_size_c.y*y_res));
      msg->label->graphick(x_res,y_res);
      last.y+=block_size.y*y_res;
      msg->time--;
      it=next;
   }
}
