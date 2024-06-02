/*File "command.h" create by debial, (Пт 17 мар 2023 13:27:47)*/
#ifndef DEBIAL_USER_COMMAND_H_SENTURY
#define DEBIAL_USER_COMMAND_H_SENTURY

#include "../../general/handler/handler.h"
#include "../perl_command/command.h"
#include "../../general/session/session.h"
#include "../../user/packet/my_packet.h"
#include "../module/BaseKlient.h"
#include "../../procs/parser.h"

class MsgUCommand : public ServerCommand{
   public:
   int handler(Session *session,Packet *input){
      UsersPack *data=(UsersPack*)input;
      printf("msg from: %s\n",data->get_name());
      printf("get msg: %s\n",data->get_packet()->data);
      return 0;
   }
};
class MsgOneWayUCommand : public ServerCommand{
   public:
   int handler(Session *session,Packet *input){
      printf("get msg: %s\n",input->data);
      return 0;
   }
};

class RequestHostUCommand : public ServerCommand{
   Klient *klient;
   public:
   RequestHostUCommand(Klient *klient_) : klient(klient_) {}
   int handler(Session *session,Packet *input){
      UsersPack *data=(UsersPack*)input;
      klient->host=GetRequestHost;
      printf("request from %s: 'responce %s' для подтверждения\n",data->get_name(),data->get_name());
      return 0;
   }
};

class FinalResponceUCommand : public ServerCommand{
   InternetApp *app;
   public:
   FinalResponceUCommand(InternetApp *app_) : app(app_){} 
   int handler(Session *session,Packet *input){
      bool result=*((bool*)(input->data));
      if(result==false){
         app->select("klient_server");
         app->del("remote_klient");
      }
      else printf("succefull connect\n");
      return 0;
   }
};

class CloseHandler : public ServerCommand{
   InternetApp *app;
   public:
   CloseHandler(InternetApp *app_) : app(app_){}
   int handler(Session *session,Packet *packet){
      close(*session);
      app->select("klient_server");
      printf("select klient_server\n");
      return 0;
   }
};

class RequestProcPerlCommand : public PerlCommand{
   Session *session;
   public:
   RequestProcPerlCommand(Session *session_) : session(session_){}
   PerlCommand* parse(const char* input){
      return this;
   }
   int handler(){
      bool data=1;
      Packet packet(RequestProcPacket,1,(char*)&data);
      session->Send(&packet);
      return 0;
   }
};

class GetResponceProcCommand : public ServerCommand{
   ProcessParser proc;
   public:
   GetResponceProcCommand() : proc(true){
      printf("succefull create proc command\n");
   }
   int handler(Session *session,Packet *input){
      proc.get(*session);
      proc.info();
      return 0;
   }
};
class ResponceHostUCommand : public ServerCommand{
   Klient *klient;
   InternetApp *app;
   InputHandler *handler_input;
   ServerHandler *Handler;
   Klient *GetConnectRemotePc(int key,sockaddr *addr){
      Klient *klient_=new Klient(handler_input,Handler,addr);
      //сюда добавлять команды для клиента да кринж 
      Handler->CloseHandler=new CloseHandler(app);
      //printf("try create proc command\n");
      //Handler->add_command(ResponceProcPacket,new GetResponceProcCommand);
      //printf("succefull add proc command\n");
      //perl->add_command("update",new RequestProcPerlCommand(klient_->session));
      //perl->add_command("scan",new MsgOneWayCommand(klient_->session));
      Packet packet(ConnectHostPacket,sizeof(key),(char*)&key);
      if(!klient_->session->Send(&packet)) return NULL;
      return klient_;
   }
   public:
   ResponceHostUCommand(Klient *klient_,InternetApp *app_,InputHandler *inp_handler,ServerHandler *Handler_) 
      : klient(klient_) ,app(app_),handler_input(inp_handler),Handler(Handler_){}
   int handler(Session *session,Packet *input){
      UsersPack *data=(UsersPack*)input;
      ResponceHostPack *pack=(ResponceHostPack*)(data->get_packet()->data);
      printf("responce to %s: succefull\n",data->get_name());
      klient->host=CompliteConnect;
      Klient *remote_pc=GetConnectRemotePc(pack->key, &pack->addr);
      if(remote_pc==NULL)
         printf("Error Connect\n");
      else{
         app->add("remote_klient",remote_pc);
         app->select("remote_klient");

      }
      return 0;
   }
};

#endif
