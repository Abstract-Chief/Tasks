/*File "box.cpp" create by debial, (Сб 15 апр 2023 21:41:27)*/
#ifndef DEBIAL_BOX_H_SENTURY
#define DEBIAL_BOX_H_SENTURY
#include "../QtObject/ActionQtObject.h"
#include "../../screen/screen.h"
#include "../Label/label.h"

#include<unordered_set>

class ActionQtBox : public ActionQtObject{
   std::unordered_set<ActionQtObject *> special[4];
   protected:
   ActionQtObject *current;
   public:
   ActionQtBox(QtObject *graphick) 
      : ActionQtObject(graphick),current(NULL){
   }
   ActionQtObject *move(int input);
   void add_special(ActionQtObject *,Direction dir);
};

//class TestBox : public ActionQtBox,public QtObject{
   //EditLabel label1,label2;
   //public:
   //TestBox(Screen *screen,coord pos) : ActionQtBox(this),QtObject(pos,coord(10,5)),
      //label1(pos,coord(10,10),9,'*','#',0,"text"),label2(coord(pos.x+12,pos.y),coord(10,10),9,'*','#',0,"text"){
         //add_special(&label1,LeftDirection);
         //add_special(&label2,RightDirection);
         //label1.set_action(&label2,RightDirection,true);
      //}
   //void graphick(float x_res,float y_res){
      //label1.BorderActionLabel::graphick(x_res, y_res);
      //label2.BorderActionLabel::graphick(x_res, y_res);
   //}
   //void select(bool type){
      //current->select(type);
   //}
   //int MyHandler(int input){
      //current->MyHandler(input);
      //return 0;
   //}

//};


#endif
