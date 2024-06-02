/*File "list.cpp" create by debial, (Вт 14 мар 2023 00:03:22)*/
#ifndef DEBIAL_LIST_H_SENTURY
#define DEBIAL_LIST_H_SENTURY
#include "../QtObject/object.h"
#include "../QtObject/ActionQtObject.h"
#include "../Geometry/geometry.h"
#include "../Label/label.h"
#include "../../screen/screen.h"
#include<vector>

class QtList : public ActionQtObject,public QtObject{
   protected:
   QtObjectHandler* handler;
   int backcur;
   public:
   int current;
   std::vector<QtObject*> labels;
   int heigh;
   char acolor,pcolor;
   QtList(coord pos,coord size,int heigh,QtObjectHandler *handler_,int acolor=1,int pcolor=0); 
   ~QtList();
   virtual void select(bool type);
   void add(QtObject *obj);
   bool del(QtObject *obj);
   virtual int MyHandler(int input);
   ActionQtObject *move(int input);
   virtual void graphick(float x_res,float y_res);
};

#endif
