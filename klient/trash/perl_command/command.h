/*File "command.h" create by debial, (Вс 05 мар 2023 22:16:38)*/
#ifndef DEBIAL_PERLCOMMAND_H_SENTURY
#define DEBIAL_PERLCOMMAND_H_SENTURY
#include "../../general/perl/perl.h"
#include "../../general/session/session.h"
#include "../../user/packet/my_packet.h"
#include "../module/BaseKlient.h"
#include <netinet/in.h>
//class LoginPerlCommand : public PerlCommand{
   //Session *session;
   //public:
   //Login user;
   //LoginPerlCommand(Session *session_) : session(session_) {}
   //PerlCommand* parse(const char* input){
      //int error=sscanf(input,"%s %s",user.name,user.pass);
      //check(2,error);
      //return this;
   //}
   //int handler(){
      //Packet *msg=new Packet(LoginPacket,sizeof(user),(char*)&user);
      //session->Send(msg);
      //printf("system: try reg user > name = %s, pass = %s\n",user.name,user.pass);
      //return 0;
   //}
//};
//class RegPerlCommand : public PerlCommand{
   //Login user;
   //Session *session;
   //public:
   //RegPerlCommand(Session *session_) : session(session_) {}
   //PerlCommand* parse(const char* input){
      //int error=sscanf(input,"%s %s",user.name,user.pass);
      //check(2,error);
      //return this;
   //}
   //int handler(){
      //Packet* msg=new Packet(RegPacket,sizeof(user),(char*)&user);
      //session->Send(msg);
      //printf("system: try login user > name = %s, pass = %s\n",user.name,user.pass);
      //return 0;
   //}
//};
//class MsgUserPerlCommand : public PerlCommand{
   //char name[32];
   //MsgPack data;
   //Session *session;
   //public:
   //MsgUserPerlCommand(Session *session_) : session(session_) {}
   //PerlCommand* parse(const char* input){
      //int error=sscanf(input,"%s %s",name,data.str);
      //check(1,error);
      //return this;
   //}
   //int handler(){
      //Packet* msg=new UsersPack(MsgUserPacket,sizeof(data),(char*)&data,name);
      //printf("send ksk msg %s\n",data.str);
      //session->Send(msg);
      //return 0;
   //}
//};
//class MsgOneWayCommand : public PerlCommand{
   //MsgPack data;
   //Session *session;
   //public:
   //MsgOneWayCommand(Session *session_) : session(session_) {}
   //PerlCommand* parse(const char* input){
      //int error=sscanf(input,"%s",data.str);
      //check(1,error);
      //return this;
   //}
   //int handler(){
      //Packet* msg=new Packet(MsgUserPacket,sizeof(data),(char*)&data);
      //printf("send msg %s\n",data.str);
      //session->Send(msg);
      //return 0;
   //}
//};

//class RequestHostPerlCommand : public PerlCommand{
   //char name[32];
   //bool data;
   //Session *session;
   //public:
   //RequestHostPerlCommand(Session *session_) : session(session_) {}
   //PerlCommand* parse(const char* input){
      //int error=sscanf(input,"%s",name);
      //check(1,error);
      //return this;
   //}
   //int handler(){
      //packet* msg=new userspack(requesthostpacket,sizeof(data),(char*)&data,name);
      //session->send(msg);
      //return 0;
   //}
//};


//class ResponceHostPerlCommand : public PerlCommand{
   //char name[32];
   //ResponceHostPack data;
   //Session *session;
   //ConsoleKlient *klient;
   //InternetApp *app;
   //public:
   //ResponceHostPerlCommand(Session *session_,ConsoleKlient *klient_,InternetApp *app_) : session(session_),klient(klient_),app(app_){}
   //PerlCommand* parse(const char* input){
      //int error=sscanf(input,"%s",name);
      //check(1,error);
      //return this;
   //}
   //int handler(){
      //if(klient->host!=1){
         //printf("not found requests\n");
      //}
      //klient->host_key=data.key=(int)((double)RAND_MAX*rand()/(RAND_MAX+(double)1))+100;
      //Server *server=(Server*)app->handlers.getnl("wait_server");
      //socklen_t size = sizeof(data.addr);
      //getsockname(server->sock, &data.addr, &size);
      //Packet* msg=new UsersPack(ResponceHostPacket,sizeof(data),(char*)&data,name);
      //session->Send(msg);
      //app->select("wait_server");
      //printf("select wait server\n");
      //return 0;
   //}
//};
//class WaiterBreakPerlCommand : public PerlCommand {
   //InternetApp *app;
   //public:
   //WaiterBreakPerlCommand(InternetApp *app_) : app(app_) {}
   //PerlCommand* parse(const char* input){
      //return this;
   //}
   //int handler(){
      //printf("stop waiter\n");
      //app->select("klient_server");
      //return 0;
   //}
//};

//class TestSizePerlCommand : public PerlCommand {
   //Session *session;
   //int count;
   //public:
   //TestSizePerlCommand(Session *session_) : session(session_){}
   //PerlCommand* parse(const char* input){
      //sscanf(input,"%d",&count);
      //return this;
   //}
   //int handler(){
      //char data[count];
      //memset(data,1,sizeof(data));
      //Packet packet(-1,count,data);
      //session->Send(&packet);
      //return 0;
   //}
//};


#endif
