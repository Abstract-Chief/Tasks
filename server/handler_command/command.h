/*File "command.cpp" create by debial, (Вс 05 мар 2023 22:09:39)*/
#ifndef DEBIAL_SERVERCOMMAND_H_SENTURY
#define DEBIAL_SERVERCOMMAND_H_SENTURY
#include "../../general/handler/handler.h"
#include "../../user/packet/my_packet.h"
#include "../../user/session/my_session.h"
#include "../../database/dhandler.h"
#include "../module/ServerBase.h"
#include <cstdlib>
#include<time.h>
#include "../server.h"

void KlientError(Session *session,ErrorTypes error);

class RegServerCommand : public ServerCommand{
   Server *server;
   public:
   RegServerCommand(Server *server_) : server(server_) {}
   int handler(Session *session,Packet *input);
};
class LoginServerCommand : public ServerCommand{
   Server *server;
   public:
   LoginServerCommand(Server *server_) : server(server_) {}
   int handler(Session *session,Packet *input);
};
class UsersServerCommand : public ServerCommand{
   Server *server;
   public:
   UsersServerCommand(Server *server_) : server(server_) {}
   int handler(Session *session,Packet *input);
};
#endif
