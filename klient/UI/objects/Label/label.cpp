/*File "label.cpp" create by debial, (Пт 10 мар 2023 20:43:00)*/
#include "label.h"
#include <curses.h>
#include <string.h>
#include <err.h>
Label::Label(coord pos_,coord size_,int max,const char *text_)
   : QtObject(pos_, size_),max_count(max){
      label_win=newwin(size.y,size.x,pos.y,pos.x);
      text=new char[max_count+1];
      del=false;
      if(text_!=NULL){
         del=true;
         count=strlen(text_);
         memcpy(text,text_,count);
      }
   }
void Label::set_text(const char *text_n){
   memcpy(text,text_n,max_count);
}
const char* Label::get_text() const{return text;}
Label::~Label(){
   if(text!=NULL && del==true) delete [] text;
   text=NULL;
}
void Label::graphick(float x,float y){
   coord n_pos(pos.x*x,pos.y*y),n_size(size.x*x,size.y*y);
   if(size.x*x<1 || size.y*y<1) return;
   if(text==NULL) return;
   wresize(label_win,size.y*y,size.x*x);
   mvwin(label_win,pos.y*y,pos.x*x);
   refresh();
   wclear(label_win);
   int count=n_size.x*n_size.y;
   if((int)strlen(text)>count){
      char buff[2]={text[count-2],text[count-1]};
      text[count-2]='.';
      text[count-1]='.';
      waddstr(label_win,text);
      text[count-2]=buff[0];
      text[count-1]=buff[1];
   }
   else
      waddstr(label_win,text);
   wrefresh(label_win);
}
void Label::coloron(int color){
   wattron(label_win, color);
}
void Label::coloroff(int color){
   wattroff(label_win, color);
}


StaticLabel::StaticLabel(coord pos,coord size,const char *text)
: Label(pos,size,size.x*size.y,text){}

ActionLabel::ActionLabel(coord pos,coord size,int max,const char *text,int acolor_,int pcolor_)
   : Label(pos,size,max,text),acolor(acolor_),pcolor(pcolor_){}


BorderActionLabel::BorderActionLabel(coord pos,coord size,int max,char space,const char *text,int acolor_,int pcolor_)
   : ActionLabel(pos+space+1,size-2*(space+1),max,text,acolor_,pcolor_),rect(pos,size){}
void BorderActionLabel::active(){
   rect.color=acolor;
}
void BorderActionLabel::disactive(){
   rect.color=pcolor;
}
void BorderActionLabel::set_pos(coord pos_,coord size_){
   rect.pos = pos_;
   rect.size = size_;
   ActionLabel::pos=pos_+2;
   ActionLabel::size=size_-3;
   max_count=size.x*size.y;
}
void BorderActionLabel::get_pos(coord *pos_,coord *size_){
   *pos_=rect.pos;
   *size_=rect.size+1;
}
void BorderActionLabel::graphick(float x_res,float y_res){
   rect.graphick(x_res,y_res);
   pos.x=rect.pos.x*x_res+1;
   pos.y=rect.pos.y*y_res+1;
   if(Label::size.x*x_res>=3 && Label::size.y*y_res>=1)
      Label::graphick(1,1);
}

EditLabel::EditLabel(coord pos,coord size,int max,char space,const char *text,int acolor_,int pcolor_) 
   : ActionQtObject(this),BorderActionLabel(pos,size,max,space,text,acolor_,pcolor_){}
int EditLabel::MyHandler(int input){
   if(input==KEY_BACKSPACE && count>0){
      count--;
      text[count]=0;
   }
   if(input>=32 && input <= 126 && count<=max_count-1){
      if(input==32) input=' ';
      text[count]=input;
      count++;
   }
   return 0;
}
void EditLabel::select(bool type){
   if(type)
      active();
   else
      disactive();
}
