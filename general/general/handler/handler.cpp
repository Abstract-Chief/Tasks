/*File "handler.cpp" create by debial, (Вс 05 мар 2023 21:04:51)*/
#include "handler.h"
int function(const unsigned char a,const unsigned char b){
   if(a>b) return 1;
   else if(a<b) return -1;
   else return 0;
}

ServerHandler::ServerHandler(ServerCommand *ConnectHandler_,ServerCommand *CloseHandler_)
   : tree(function){
   ConnectHandler=ConnectHandler_;
   CloseHandler=CloseHandler_;
}
bool ServerHandler::handler(Session *session,Packet *packet){//true если несуществующий тип команды
   ServerCommand* command=tree.get(packet->type);
   if(command==NULL) return true;
   command->handler(session,packet);
   return false;
}
bool ServerHandler::add_command(unsigned char id,ServerCommand *command){
   if(tree.check(id)) return true;
   tree.add(id,command);
   return false;
}
bool ServerHandler::update_command(unsigned char id,ServerCommand *command){
   tree.add(id,command);
   return false;
}
bool ServerHandler::check(unsigned char id){
   return tree.check(id);
}
