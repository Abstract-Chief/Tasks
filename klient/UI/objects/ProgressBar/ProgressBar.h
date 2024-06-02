/*File "ProgressBar.cpp" create by debial, (Ср 12 апр 2023 13:22:51)*/
#ifndef DEBIAL_PROGRESSBAR_H_SENTURY
#define DEBIAL_PROGRESSBAR_H_SENTURY
#include "../QtObject/object.h"
#include "../Label/label.h"
class ProgressBar : public QtObject{
   static cchar_t ProgressSymbol[8];
   static char size_progress;
   static void set_symbol(){
      setcchar(&ProgressSymbol[0], L"▌", 0, 0, NULL); // ▌
      setcchar(&ProgressSymbol[1], L"▌", 0, 0, NULL); // ▌
      setcchar(&ProgressSymbol[2], L"▌", 0, 0, NULL); // ▌
      setcchar(&ProgressSymbol[3], L"▌", 0, 0, NULL); // ▌
      setcchar(&ProgressSymbol[4], L"▋", 0, 0, NULL); // ▋
      setcchar(&ProgressSymbol[5], L"▊", 0, 0, NULL); // ▊
      setcchar(&ProgressSymbol[6], L"▉", 0, 0, NULL); // ▉
      setcchar(&ProgressSymbol[7], L"█", 0, 0, NULL); // █ 
      size_progress=8;
      set_symbol_type=true;
   }
   public:
   static bool set_symbol_type;
   unsigned char percent;
   ProgressBar(coord pos,coord size);
   void graphick(float x_res,float y_res);
};

class ProgressBarBorderOut : public ProgressBar{
   WINDOW *bwin;
   public:
   ProgressBarBorderOut(coord pos,coord size);
   ~ProgressBarBorderOut();
   void graphick(float x_res,float y_res);
};
class ProgressBarBorder : public ProgressBar{
   WINDOW *bwin;
   public:
   ProgressBarBorder(coord pos,coord size);
   ~ProgressBarBorder();
   void graphick(float x_res,float y_res);
};

class InfoProgressBar : public ProgressBarBorder{
   protected:
   Label label;
   public:
   InfoProgressBar(coord pos,coord size,const char *info_);
   void graphick(float x_res,float y_res);
};

#endif
