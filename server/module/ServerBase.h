#ifndef SERVER_H_SENTURY
#define SERVER_H_SENTURY
#include "../../general/perl/perl.h"
#include "../../general/handler/handler.h"
#include "../../general/inet_base/InternetBase.h"
// ServerBase.cpp
class ServerBase : public InternetBase{
   Session *Listen();
   fd_set fdset_ret;
   struct sockaddr addr;
   int count;
   public:
   Socket sock;
   int countfd;
   int clientfd[FD_SETSIZE];
   Session *clientses[FD_SETSIZE];
   ServerBase(const char *ip,int port,int queue,InputHandler *handler_input,ServerHandler *handler);

   int handler();
   int add_session(Session *session);
   void set_handler(ServerHandler *handler);

   operator int();
   void Close();
   bool CloseConnection(int id);

};
#endif
