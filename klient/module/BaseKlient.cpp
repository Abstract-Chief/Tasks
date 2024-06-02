/*File "BaseKlient.cpp" create by debial, (Вт 14 мар 2023 23:10:19)*/
#include "BaseKlient.h"
#include <curses.h>
Klient::Klient(InputHandler *handler_input,ServerHandler *handler_,char *ip) 
    : ServerBase(NULL,0,10,handler_input,handler_),ks_ses(ip,0){
   ks_ses.Conect(ip,1223);
   add_session(&ks_ses);
}
void Klient::add_pcon(const char *name,Connection *pack){
   connection.insert(std::make_pair(name,pack));
}
void Klient::del_pcon(const char *name){
   connection.erase(name);
}
void Klient::add_valid_key(const char *name,int key){
   valid_key.insert(std::make_pair(key,name));
}
Connection *Klient::get_connection(int key){
   return get_connection(valid_key.at(key));
}
Connection *Klient::get_connection(std::string name){
   try{
      return connection.at(name);

   }catch(std::out_of_range& e){
      return NULL;
   }
}
bool Klient::check_key(int key){
   try{
      valid_key.at(key);
      return true;

   }catch(std::out_of_range& e){
      return false;
   }
}
void Klient::del_valid_key(const char *name){
   valid_key.erase(connection.at(name)->pack.key);
}
