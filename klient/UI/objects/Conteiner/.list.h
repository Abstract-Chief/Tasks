/*File "list.cpp" create by debial, (Вт 14 мар 2023 00:03:22)*/
#ifndef DEBIAL_LIST_H_SENTURY
#define DEBIAL_LIST_H_SENTURY
#include "../QtObject/object.h"
#include "../QtObject/ActionQtObject.h"
#include "../Geometry/geometry.h"
#include "../Label/label.h"
#include "../../screen/screen.h"

class QtList : public ActionQtObject,public QtObject{
   public:
   char a_ch,p_ch;
   int space;
   ActionQtObject *first,*last;
   void setting_object(ActionQtObject *object);
   QtList(coord pos,coord size,int space_); 
   ~QtList();
   void select(bool type);
   void add(ActionQtObject *object);
   void add_list(QtList *list);
   virtual int MyHandler(int input);
   void graphick(float x_res,float y_res);
};

#endif
