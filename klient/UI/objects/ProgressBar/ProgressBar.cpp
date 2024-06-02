/*File "ProgressBar.cpp" create by debial, (Ср 12 апр 2023 13:22:51)*/
#include "ProgressBar.h"
#include <curses.h>
bool ProgressBar::set_symbol_type=false;   
char ProgressBar::size_progress=0;
cchar_t ProgressBar::ProgressSymbol[8];
ProgressBar::ProgressBar(coord pos,coord size) : QtObject(pos,size),percent(0){
   if(ProgressBar::size_progress==0) set_symbol();
}
void ProgressBar::graphick(float x_res,float y_res){
   if(percent>100) percent=100;
   unsigned char cost=100.0/size.x*x_res;
   int color=(percent > 50 ? 1 : 2);
   //wattron(win,COLOR_PAIR(color));
   for(int x=0;x<percent/cost;x++)
      for(int y=0;y<size.y*y_res;y++)
         mvwadd_wch(win,pos.y*y_res+y,pos.x*x_res+x,&ProgressSymbol[7]);
   int index=(percent%cost)/(cost/size_progress)-1;
   if(index<0) return;
   for(int y=0;y<size.y;y++)
      mvwadd_wch(win,pos.y*y_res+y,pos.x*x_res+(float)percent/cost,&ProgressSymbol[index]);
   //wattroff(win,COLOR_PAIR(color));
}
ProgressBarBorder::ProgressBarBorder(coord pos,coord size) : ProgressBar(pos+1,size-2){
   bwin=newwin(size.y,size.x,pos.y,pos.x);
   wrefresh(bwin); // обновление экрана 
   refresh();
}
void ProgressBarBorder::graphick(float x_res,float y_res){
   wresize(bwin, (size.y+2) * y_res, (size.x+2) * x_res);
   mvwin(bwin, (pos.y-1) * y_res, (pos.x-1) * x_res);
   box(bwin, 0,0);
   wrefresh(bwin);
   ProgressBar::graphick(x_res, y_res);
   refresh();
}
ProgressBarBorder::~ProgressBarBorder(){
   delwin(bwin);
}
ProgressBarBorderOut::ProgressBarBorderOut(coord pos,coord size) : ProgressBar(pos+1,size-2){
   bwin=newwin(size.y+2,size.x+2,pos.y-1,pos.x-1);
   wrefresh(bwin); // обновление экрана 
   refresh();
}
void ProgressBarBorderOut::graphick(float x_res,float y_res){
   wresize(bwin, size.y * y_res, size.x * x_res);
   mvwin(bwin, pos.y * y_res, pos.x * x_res);
   box(bwin, 0,0);
   wrefresh(bwin);
   refresh();
   ProgressBar::graphick(x_res, y_res);
}
ProgressBarBorderOut::~ProgressBarBorderOut(){
   delwin(bwin);
}
InfoProgressBar::InfoProgressBar(coord pos,coord size,const char *info_) 
   : ProgressBarBorder(pos,size),label(pos,size,strlen(info_),info_){
}
void InfoProgressBar::graphick(float x_res,float y_res){
   ProgressBarBorder::graphick(x_res,y_res);
   label.graphick(x_res,y_res);
}
