/*File "server.h" create by debial, (Вс 14 мая 2023 23:30:55)*/
#ifndef DEBIAL_SERVER_H_SENTURY
#define DEBIAL_SERVER_H_SENTURY
#include"module/ServerBase.h"
#include <unordered_map>
class Server : public ServerBase{
   std::unordered_map<std::string,int> online;
   public:
   Server(const char *ip, int port, int queue, InputHandler *handler_input,ServerHandler *handler) 
      : ServerBase(ip,port,queue,handler_input,handler){}
   void login(const char *name,int n){
      online[name]=n;
   }
   int get_login(const char *name){
      try {
         return online.at(name);
      } catch (std::out_of_range &e) {
         return -1;
      }
   }
   void delogin(const char *name){
      if(online.find(name)!=online.end())
         online.erase(name);
   }
};


#endif
