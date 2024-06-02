#include "session.h"
void error(const char *msg){
   printf("%s\n",msg);
   exit(1);
}
Socket::Socket(int sock_) : sock(sock_){}
Socket::Socket(const char *ip,int port){
   sock=socket(AF_INET,SOCK_STREAM,0);
   if(sock<0){
      error("mysocket");
   }
   struct sockaddr_in socket_addr;
   socket_addr.sin_family=AF_INET;
   socket_addr.sin_port=htons(port);
   if(ip!=NULL) socket_addr.sin_addr.s_addr=inet_addr(ip);
   else socket_addr.sin_addr.s_addr=htons(INADDR_ANY);
   if(bind(sock,(struct sockaddr*)&socket_addr,sizeof(socket_addr))<0)
      error("bind");
}
Socket::operator int(){
   return sock;
}
struct sockaddr_in GetServAddr(char *ip,int port){
   struct sockaddr_in server_addr;
   server_addr.sin_family=AF_INET;
   server_addr.sin_port=htons(port);
   server_addr.sin_addr.s_addr=inet_addr(ip);
   if(server_addr.sin_addr.s_addr<0)
      error("addr");
   return server_addr;
}

