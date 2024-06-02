/*File "geometry.cpp" create by debial, (Пт 10 мар 2023 20:34:57)*/
#ifndef DEBIAL_GEOMETRY_H_SENTURY
#define DEBIAL_GEOMETRY_H_SENTURY

#include "../QtObject/object.h"
#include <curses.h>
#include <math.h>
#include <iostream>

class Line : public QtObject{
   public:
   char ch;
   Line(coord s_,coord e_,char ch_='#');
   virtual ~Line(){}
   void graphick(float x_res=1,float y_res=1);
};
// b--c
// |  |
// a--d
class Rectangle : public QtObject{
   WINDOW *rect;
   public:
   int color;
   Rectangle(coord pos,coord size,int color=0);
   ~Rectangle();
   void graphick(float x_res=1,float y_res=1);
};
//class Circle : public QtObject{
   //coord o;
   //int r;
   //char ch;
   //public:
   //Circle(coord center,int radius,char ch_='#');
   //virtual void graphick();
//};

#endif
