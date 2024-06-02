/*File "my_session.h" create by debial, (Вт 14 мар 2023 23:22:35)*/
#ifndef DEBIAL_MY_SESSION_H_SENTURY
#define DEBIAL_MY_SESSION_H_SENTURY

#include "../../general/session/session.h"
#include "../packet/my_packet.h" 

struct LoginStorage : public Storage{
   bool login;
   char name[32];
   void set_name(char *name_){
      memcpy(name,name_,32);
   }
};

#endif
