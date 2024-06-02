/*File "screen.cpp" create by debial, (Сб 11 мар 2023 17:36:36)*/
#ifndef DEBIAL_SCREEN_H_SENTURY
#define DEBIAL_SCREEN_H_SENTURY
#include "../objects/QtObject/ActionQtObject.h"
#include "../objects/QtObject/object.h"
#include <string.h>
#include <err.h>

#include <stdexcept>
#include <unordered_map>

class Screen;
class KeyHandler{
   public:
   virtual bool handler(Screen *screen) = 0;
   virtual ~KeyHandler(){}
};

class Screen{
   public:
   WINDOW *window;
   ActionQtObject* action;
   struct Block{
      QtObject* obj;
      bool type;
      operator QtObject*() const{return obj;}
      Block(QtObject* obj_,bool type_) : obj(obj_),type(type_){}
   };
   struct ABlock{
      ActionQtObject* obj;
      bool type;
      operator ActionQtObject*() const{return obj;}
      ABlock(ActionQtObject* obj_,bool type_) : obj(obj_),type(type_){}
   };
   private:
   coord size;
   std::unordered_map<int,Block*> storage;
   std::unordered_map<int,ABlock*> ActionStorage;
   std::unordered_map<int,KeyHandler*> ButtonStorage;
   char debug;
   int count;
   int ActionCount;
   void rendering(float x_res,float y_res);
   void Arendering(float x_res,float y_res);
   void DebugGraphick();
   public:
   void render();
   void add(int name,QtObject *object,bool del);
   void add_action(int name,ActionQtObject *object,bool del);
   void add_button(int name,KeyHandler *object);
   inline void handler(int input){
      try {
         KeyHandler *key=ButtonStorage.at(input);
         key->handler(this);
      } catch (std::out_of_range& e) {
         if(action==NULL) return;
         ActionQtObject *new_action=action->handler(input);
         if(new_action!=NULL) {
            action->select(false);
            action=new_action;
            action->select(true);
         }
      }
   }
   void set_action(int name);
   QtObject *get(int name);
   ActionQtObject *get_action(int name);
   Screen();
   Screen(WINDOW *win,coord base_size,bool debug_=false);
   ~Screen();
};

#endif
