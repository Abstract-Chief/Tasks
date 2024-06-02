/*File "handler.cpp" create by debial, (Вс 05 мар 2023 21:04:52)*/
#ifndef DEBIAL_COMMAND_H_SENTURY
#define DEBIAL_COMMAND_H_SENTURY
#include "../packet/packet.h"
#include "../session/session.h"
#include "../perl/tree.h"
#include "../perl/perl.h"

class ServerCommand{
   public:
   virtual int handler(Session*,Packet*) = 0;
};

class ServerHandler{
   BinaryTree<unsigned char,ServerCommand*> tree;
   public:
   ServerCommand *ConnectHandler;
   ServerCommand *CloseHandler;
   ServerHandler(ServerCommand *ConnectHandler_,ServerCommand *CloseHandler_);
   bool handler(Session *session,Packet *packet);//true если несуществующий тип команды
   bool add_command(unsigned char id,ServerCommand *);
   bool update_command(unsigned char id,ServerCommand *);
   bool check(unsigned char id);
};

#endif
