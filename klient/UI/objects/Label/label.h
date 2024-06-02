/*File "label.cpp" create by debial, (Пт 10 мар 2023 20:26:14)*/
#ifndef DEBIAL_LABEL_H_SENTURY
#define DEBIAL_LABEL_H_SENTURY
#include "../QtObject/object.h"
#include "../Geometry/geometry.h"
#include "../QtObject/ActionQtObject.h"
#include <curses.h>
#include <stdio.h>
#include <string.h>

class Label : public QtObject{
   bool del;
   protected:
   int count,max_count;
   WINDOW *label_win;
   public:
   char *text;
   Label(coord pos_,coord size_,int max_count,const char *text_=NULL);
   virtual ~Label();
   const char* get_text() const;
   void set_text(const char *text_n);
   virtual void graphick(float x_res,float y_res);
   virtual void coloron(int color);
   virtual void coloroff(int color);
};

class StaticLabel : public Label{
   public:
   StaticLabel(coord pos,coord size,const char *text=NULL);
};
class ActionLabel : public Label{
   protected:
   int acolor,pcolor;
   public:
   ActionLabel(coord pos,coord size,int max,const char *text=NULL,int acolor_=1,int pcolor_=0);
   virtual void active() = 0;
   virtual void disactive() = 0;
};

class BorderActionLabel : public ActionLabel{
   public:
   Rectangle rect;
   BorderActionLabel(coord pos,coord size,int max,char space=1,const char *text=NULL,int acolor_=1,int pcolor_=0);
   void active();
   void disactive();
   virtual void set_pos(coord pos_,coord size_);
   virtual void get_pos(coord *pos_,coord *size_);
   virtual void graphick(float x_res,float y_res);
};
class EditLabel : public ActionQtObject,public BorderActionLabel{
   public:
   EditLabel(coord pos,coord size,int max,char space=0,const char *text=NULL,int acolor_=1,int pcolor_=0);
   int MyHandler(int input);
   void select(bool type);
};
#endif
