/*File "notice.cpp" create by debial, (Пн 17 апр 2023 21:02:27)*/
#ifndef DEBIAL_NOTICE_H_SENTURY
#define DEBIAL_NOTICE_H_SENTURY

#include "../QtObject/object.h"
#include "../Label/label.h"
#include<list>


class QtNotice : public QtObject{
   struct Notice{
      BorderActionLabel *label;
      int time;
   };
   std::list<Notice*> notice;
   int max_notice;
   coord block_size;
   public:
   QtNotice(coord pos,coord size,int heigh,int max_notice_);
   bool add(const char *text,int time,int color);
   void graphick(float x_res,float y_res);
};

#endif
