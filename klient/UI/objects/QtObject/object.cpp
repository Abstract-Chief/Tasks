/*File "object.cpp" create by debial, (Вт 11 апр 2023 23:26:38)*/
#include "object.h"
bool coord::operator==(const coord& rhs) const{
   return (x==rhs.x && y==rhs.y);
}
const coord coord::operator+(const int a) const{
   return coord(x+a,y+a);
}
const coord coord::operator+(const coord a) const{
   return coord(x+a.x,y+a.y);
}
const coord coord::operator-(const int a) const{
   return coord(x-a,y-a);
}
const coord coord::operator-(const coord a) const{
   return coord(x-a.x,y-a.y);
}

QtObject::QtObject(coord pos_,coord size_,WINDOW *win_) : win(win_),pos(pos_),size(size_){}
void QtObject::set_pos(coord pos_,coord size_){
   pos = pos_;
   size = size_;
}
void QtObject::get_pos(coord *pos_,coord *size_){
   *pos_=pos;
   *size_=size;
}
void QtObject::coloron(int color){
   wattron(win, color);
}
void QtObject::coloroff(int color){
   wattroff(win, color);
}
