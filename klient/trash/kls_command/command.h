/*File "command.h" create by debial, (Вт 28 мар 2023 11:37:14)*/
#ifndef DEBIAL_KLS_COMMAND_H_SENTURY
#define DEBIAL_KLS_COMMAND_H_SENTURY
#include "../../general/handler/handler.h"
#include "../../user/packet/my_packet.h"
#include "../../database/dhandler.h"
#include "../module/BaseKlient.h"
#include "../user_command/command.h"
#include "../../procs/parser.h"

//class KLSBreakCommand : public PerlCommand{
   //ConsoleKlient *klient;
   //InternetApp *app;
   //public:
   //KLSBreakCommand(ConsoleKlient *klient_,InternetApp *app_) : klient(klient_),app(app_) {}
   //PerlCommand* parse(const char* input){
      //return this;
   //}
   //int handler(){
      //printf("close remote connection\n");
      //app->del("remote_klient");
      //app->select("klient_server");
      //return 0;
   //}
//};
//class ResponceProcCommand : public ServerCommand{
   //ProcessParser proc;
   //public:
   //ResponceProcCommand() : proc(false){
      //printf("create proc command\n");
   //}
   //int handler(Session *session,Packet *input){
      //printf("update proc\n");
      //bool data;
      //Packet packet(ResponceProcPacket,1,(char*)&data);
      //session->Send(&packet);
      //proc.send(*session);
      //return 0;
   //}
//};
class KLSConnectCommand : public ServerCommand{
   Klient *klient;
   InternetApp *app;
   ServerHandler *Handler;
   public:
   KLSConnectCommand(Klient *klient_,InternetApp *app_,ServerHandler *handler_) : klient(klient_),app(app_),Handler(handler_) {}
   int handler(Session *session,Packet *input){
      int key=*((int*)input->data);
      printf("try connect key %d\n",key);
      bool result=false;
      if(key==klient->host_key){
         printf("succeful connect\n");
         //Perl *perl= new Perl("");
         Handler->CloseHandler=new CloseHandler(app);
         //perl command
         //perl->add_command("break", new KLSBreakCommand(klient,app));
         //handler server command
         //Handler->add_command(RequestProcPacket,new ResponceProcCommand());
         //end
         //Klient *remote_klient=new Klient(perl,Handler,*session);
         //app->add("remote_klient",remote_klient);
         //app->select("remote_klient");
         //result=true;
      }
      Packet packet(FinalResponseHostPacket,sizeof(bool),(char*)&result);
      session->Send(&packet);
      return 0;
   }
};



#endif
