#include "session.h"
#include <netinet/in.h>
#include <sys/socket.h>
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
   if(bind(sock,(sockaddr*)&socket_addr,sizeof(socket_addr))<0)
      error("bind");
   socklen_t size = sizeof(addr);
   getsockname(sock, &addr, &size);
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

Session::Session(const char *ip,int port) : sock(ip,port),conect(false),pos(-1){}
Session::Session() : sock(NULL,0),conect(false),pos(-1){}
Session::Session(int sock_,struct sockaddr_in *addr_,const short pos_) : sock(sock_),conect(true),pos(pos_){
   //memcpy(&addr,addr_,sizeof(addr));
   ip_client=new char[16];
   ip_int=addr_->sin_addr.s_addr;
   inet_ntop(AF_INET, &addr_->sin_addr, ip_client, 16);
   port_client=ntohs(addr_->sin_port);
}
Session::~Session(){
   close(sock);
}
bool Session::Conect(char *ip,int port){
   struct sockaddr_in server_addr=GetServAddr(ip,port);
   socklen_t size=(socklen_t)sizeof(server_addr);
   if(connect(sock,(struct sockaddr *)&server_addr,size)<0)
      return false;
   return conect=true;
}
bool Session::Conect(sockaddr *new_addr){
   socklen_t size=(socklen_t)sizeof(sockaddr_in);
   if(connect(sock,new_addr,size)<0){
      if(errno==ECONNREFUSED) error("connect error: server off");
      error("connect error: unknown");
   }
   return conect=true;
}
bool Session::Send(const Packet* data){
   if(write(sock,&data->type,sizeof(data->type))<0) return false;
   if(write(sock,&data->size,sizeof(data->size))<0) return false;
   if(write(sock,data->data,data->size)<0) return false;
   return true;
}
Packet *Session::Read(){
   Packet *buffer=new Packet;
   
   int result=read(sock,&buffer->type,sizeof(buffer->type));
   printf("%d",buffer->type);
   if(result<=0 || buffer->type<0 || buffer->type>255){
      delete buffer;
      return NULL;}
   result=read(sock,&buffer->size,sizeof(buffer->size));
   if(result<=0 || (buffer->size<=0 || buffer->size>=128000)){
      delete buffer;
      return NULL;}
   buffer->data=new char[buffer->size];
   result=read(sock,buffer->data,buffer->size);
   if(result<=0){
      delete buffer;
      return NULL;}
   return buffer;
}
char *Session::getip(){
   return ip_client;
}
int Session::getip_int(){
   return ip_int;
}
int Session::getport(){
   return port_client;
}
Session::operator int(){
   return sock;
}
