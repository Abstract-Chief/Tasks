#ifndef SESSION_H_SENTURY
#define SESSION_H_SENTURY
#include <asm-generic/errno.h>
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
void error(const char *msg);
struct sockaddr_in GetServAddr(char *ip,int port);


class Socket{
   int sock;
   public:
   Socket(int sock_);
   Socket(const char *ip,int port);
   operator int();
};

template<class TYPE>
class Session{
   private:
      Socket sock;
      bool conect;
   public:
      
   Session(const char *ip,int port) : sock(ip,port),conect(false){}
   Session(int sock_,struct sockaddr addr) : sock(sock_),conect(true){}
   bool Conect(char *ip,int port){
      struct sockaddr_in server_addr=GetServAddr(ip,port);
      socklen_t size=(socklen_t)sizeof(server_addr);
      if(connect(sock,(struct sockaddr *)&server_addr,size)<0){
         if(errno==ECONNREFUSED) error("connect error: server off");
         error("connect error: unknown");
      }
      return conect=true;
   }
   void Send(const TYPE* data){
      if(write(sock,data,sizeof(TYPE))<0) error("send error");
   }
   TYPE *Read(){
      TYPE *buffer=new TYPE;
      int result=read(sock,buffer,sizeof(TYPE));
      if(result==-1) error("Error read");
      else if(result==0){
         delete buffer;
         return NULL;}
      return buffer;
   }
   operator int(){
      return sock;
   }
};
class String{
   char msg[32];
   public:
   String(){}
   String(const char *string){
      strncpy(msg,string,32);
   };
   operator char*(){return msg;}
};
#endif
