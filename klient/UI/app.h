/*File "app.cpp" create by debial, (Пн 24 апр 2023 17:58:46)*/
#ifndef DEBIAL_APP_H_SENTURY
#define DEBIAL_APP_H_SENTURY

#include<unordered_map>
#include "screen/screen.h"

enum BaseColors{
   ActionColor=1,
   PassiveColor=0,
   ChooseColor=2,
};

class GraphickApp{
   std::unordered_map<int,Screen*> screens;
   public:
   Screen* current;
   GraphickApp();
   ~GraphickApp();
   void add(int id,Screen *Screen);
   void del(int id);
   void set(int id);
   Screen *get(int id);
};

#endif
