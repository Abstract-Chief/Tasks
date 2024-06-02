/*File "geometry.cpp" create by debial, (Пт 10 мар 2023 18:11:49)*/
#include "../QtObject/object.h"
#include "geometry.h"
#include <curses.h>
#include <math.h>
#include <sys/types.h>
int max(int a,int b){
   return (a>b ? a : b);
}
#include <iostream>

Rectangle::Rectangle(coord pos_,coord size_,int color_)
   : QtObject(pos_,size_),rect(newwin(size_.y,size_.x,pos_.y,pos_.x)),color(color_){
      wrefresh(rect);
      refresh();
   }

void Rectangle::graphick(float x,float y){
   wclear(rect);
   wresize(rect,size.y*y,size.x*x);
   mvwin(rect,pos.y*y,pos.x*x);
   refresh();
   wclear(rect);
   wattron(rect,COLOR_PAIR(color)); // включение цветовой пары
   box(rect,0,0);
   wattroff(rect,COLOR_PAIR(color));
   wrefresh(rect);
}
Rectangle::~Rectangle(){
   delwin(rect);
}



Line::Line(coord s_,coord e_,char ch_) : QtObject(s_,e_),ch(ch_){}

void Line::graphick(float x_res,float y_res){
   int y1=pos.x*x_res,y2=size.x*x_res,x1=pos.y*y_res,x2=size.y*y_res;
   const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
   if(steep){
   std::swap(x1, y1);
   std::swap(x2, y2);
   }
   if(x1 > x2){
      std::swap(x1, x2);
      std::swap(y1, y2);
   }
   const float dx = x2 - x1;
   const float dy = fabs(y2 - y1);
   float error = dx / 2.0f;
   const int ystep = (y1 < y2) ? 1 : -1;
   int y_ = (int)y1;
   const int maxX = (int)x2;
   for(int x=(int)x1; x<=maxX; x++){
      if(steep)
         mvwaddch(win,y_,x,ch);
      else
         mvwaddch(win,x,y_,ch);
      error -= dy;
      if(error < 0)
      {
        y_ += ystep;
        error += dx;
      }
   }
}
