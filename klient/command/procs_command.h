/*File "procs_command.cpp" create by debial, (Вс 14 мая 2023 21:32:19)*/
#ifndef DEBIAL_PROCS_COMMAND_H_SENTURY
#define DEBIAL_PROCS_COMMAND_H_SENTURY

#include "../module/BaseKlient.h"
#include "../../procs/parser.h"
#include"../UI//screen/screen.h"
#include"../config/ui.h"
#include "../UI/objects/tasks/ProcessList.h"
#include "../UI/objects/Notice/notice.h"

extern GraphickApp *GraphApp;
void GetProcCommand(Session *session,int key);
class RequestProcHandler : public ServerCommand{
   Klient *klient;
   public:
   RequestProcHandler(Klient *klient_) : klient(klient_){}
   int handler(Session *session,Packet *input){
      KeyPack *pack=(KeyPack*)input;
      int key=pack->get_key();
      Connection *con=klient->get_connection(key);
      if(con!=NULL){
         bool zero=1;
         KeyPack pack(ResponceProcPacket,sizeof(bool),(char*)&zero,key);
         session->Send(&pack);
         con->parser.send((int)*session);
      }
      return 0;
   }
};
class ResponceProcHandler : public ServerCommand{
   Klient *klient;
   public:
   ResponceProcHandler(Klient *klient_) : klient(klient_){}
   int handler(Session *session,Packet *input){
      KeyPack *pack=(KeyPack*)input;
      int key=pack->get_key();
      Connection *con=klient->get_connection(key);
      if(con!=NULL){
         con->parser.get((int)*session);
         ProcessList *list=(ProcessList*)(GraphApp->get(TaskScreen)->get_action(ProcessListObject));
         list->update(&con->parser);
      }
      return 0;
   }
};

#endif
