#ifndef SESSION_H_SENTURY
#define SESSION_H_SENTURY
#include <sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include <errno.h>
// session.cpp
#include "../packet/packet.h"
void error(const char *msg);
struct sockaddr_in GetServAddr(char *ip,int port);


class Socket{
   int sock;
   public:
   struct sockaddr addr;
   Socket(int sock_);
   Socket(const char *ip,int port);
   operator int();
};

struct Storage{
   virtual void info(){
      printf("this session not user storage\n");
   }
};

class Session{
   private:
      Socket sock;
      bool conect;
      char *ip_client;
      int port_client,ip_int;
   public:
      int pos;
      Storage *storage;
      sockaddr addr;
   Session(const char *ip,int port);
   Session(int sock_,struct sockaddr_in *addr,const short pos_);
   ~Session();
   bool Conect(char *ip,int port);
   bool Conect(sockaddr *addr);
   bool Send(const Packet* data);
   Packet *Read();
   char *getip();
   int getip_int();
   int getport();
   operator int();
};
#endif
