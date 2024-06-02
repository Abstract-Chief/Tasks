/*File "object.cpp" create by debial, (Пт 10 мар 2023 18:08:35)*/
#ifndef DEBIAL_OBJECT_H_SENTURY
#define DEBIAL_OBJECT_H_SENTURY

#include <ncurses.h>

struct coord{
   short x,y;
   coord(short x,short y) : x(x), y(y){}
   bool operator==(const coord& rhs) const;
   const coord operator+(const int a) const;
   const coord operator+(const coord a) const;
   const coord operator-(const int a) const;
   const coord operator-(const coord a) const;
};

class QtObject{
   protected:
   WINDOW *win;
   public:
   coord pos,size;
   QtObject(coord pos_,coord size_,WINDOW *win_=stdscr);
   void set_window(WINDOW *win_){win=win_;}
   virtual void set_pos(coord pos_,coord size_);
   virtual void get_pos(coord *pos_,coord *size_);

   virtual ~QtObject(){}
   virtual void graphick(float x_res=1,float y_res=1) = 0;
   virtual void coloron(int color);
   virtual void coloroff(int color);
};

class QtObjectHandler{
   public:
      virtual int handler(QtObject *obj,int key=0) = 0;
};

#endif
