/*File "TaskObject.cpp" create by debial, (Чт 13 апр 2023 20:55:34)*/
#ifndef DEBIAL_TASKOBJECT_H_SENTURY
#define DEBIAL_TASKOBJECT_H_SENTURY
#include "../ProgressBar/ProgressBar.h"
#include "../Label/label.h"
#include "../Conteiner/list.h"
#include "../Button/button.h"
#include "../Conteiner/box.h"
#include "../../../../procs/parser.h"
#include <curses.h>
#include <string.h>
#include <vector>
#include <math.h>

//procs
//klient

//class MemoryInfo : public InfoProgressBar{
   //public:
   //MemoryInfo(coord pos_,coord size_);
   //void set_percent(unsigned char a);
   //virtual QtObject* copy() const;
//};

//class CPUInfo : public QtObject{
   //std::vector<CPU*> *cpu;
   //std::vector<InfoProgressBar*> graphick_cpu;
   //public:
   //CPUInfo(std::vector<CPU*> *cpu_,coord pos,coord size);
   //void graphick(float x_res,float y_res);
//};


class ProccentLabel : public QtObject{
   ProgressBar bar;
   public:
   bool type;
   float percent;
   ProccentLabel(coord pos,coord size,bool type_);
   void graphick(float x,float y);
};
//будет хранить указатели на переменные процесса 
class ProcessInfo : public QtObject{
   Label *name_label;
   ProccentLabel *cpu,*mem;
   char *status;
   long *parent,
        *RmSize,//resident memmory
        *VmSize,//virtual memmory
        *SHmSize;//shared memmory
   unsigned long long *all_ticks;
   unsigned long long *ticks;
   char *name;
   public:
   long *pid;
   ProcessInfo(Process *process,unsigned long long *all_ticks_,coord pos={0,0},coord size={0,0});
   void graphick(float x,float y);
};

class ConnectionList : public QtList{
   Label *label_n;
   Rectangle *rect;
   char *text;
   int len_r;
   public:
   ConnectionList(coord pos, coord size, int heigh,QtObjectHandler *handler,const char *text_,char acolor=1,char pcolor=0);
   void set_handler(QtObjectHandler *handler_);
   int MyHandler(int input);
   void select(bool type_s);
   void graphick(float x_res,float y_res);
   ~ConnectionList();
};

class Slider : public ActionQtObject,public QtObject{
   public: 
   int color;
   bool type;
   char key;
   BorderActionLabel *block[2];
   Slider(coord pos,coord size,char key_,const char *t1,const char *t2,int color);
   Slider(coord pos,coord size,char key_,BorderActionLabel *blocka_,BorderActionLabel *b_,int color);
   ~Slider();
   int MyHandler(int input);
   void select(bool type_s);
   void graphick(float x_res,float y_res);
};


class LoginHandler : public ActionQtBox,public QtObject{
   public:
   EditLabel *login,*pass;
   BorderActionLabel *label_but;
   Button *button;
   Slider *slider;
   LoginHandler(coord pos) 
      : ActionQtBox(this),QtObject(pos,coord(16,11)){
      coord ed_size(16,3);
      login = new EditLabel(coord(pos.x,pos.y+1),ed_size,16,0);
      current=login;
      pass = new EditLabel(coord(pos.x,pos.y+ed_size.y+2),ed_size,16,0);
      slider = new Slider(coord(pos.x,pos.y+((ed_size.y)*2)+2),coord(10,3),'f',"l","r",2);
      label_but=new BorderActionLabel(coord(slider->pos.x+slider->size.x+1,slider->pos.y),
            coord(16-slider->size.x,slider->size.y),5,0,"push");
      button = new Button(label_but,'f',NULL);
      login->set_action(pass,DownDirection);
      pass->set_action(slider,DownDirection);
      slider->set_action(button,RightDirection);
      button->set_action(pass,UpDirection,false);

      add_special(login,LeftDirection);
      add_special(login,UpDirection);
      add_special(login,RightDirection);
      add_special(pass,LeftDirection);
      add_special(pass,RightDirection);
      add_special(slider,LeftDirection);
      add_special(slider,DownDirection);
      add_special(button,RightDirection);
      add_special(button,DownDirection);
   }
   ~LoginHandler(){
      delete login;
      delete pass;
      delete button;
      delete label_but;
      delete slider;
   }
   void graphick(float x_res,float y_res){
      mvwaddstr(win,pos.y*y_res,(pos.x+6)*x_res,"login");
      mvwaddstr(win,(pos.y+4)*y_res,(pos.x+6)*x_res,"pass");
      login->BorderActionLabel::graphick(x_res,y_res);
      pass->BorderActionLabel::graphick(x_res,y_res);
      slider->graphick(x_res,y_res);
      button->graphick->graphick(x_res,y_res);
   }
   int MyHandler(int input){
      current->MyHandler(input);
      return 0;
   }
   void select(bool type){
      current->select(type);
   }
};
#endif
