/*File "ksk_command.cpp" create by debial, (Пт 05 мая 2023 15:49:48)*/
#ifndef DEBIAL_KSK_COMMAND_H_SENTURY
#define DEBIAL_KSK_COMMAND_H_SENTURY

#include "../module/BaseKlient.h"
#include "../config/ui.h"
#include "../UI/objects//Conteiner/list.h"
#include "../UI/objects/Notice/notice.h"
#include "../UI/objects/tasks/TaskObject.h"


extern GraphickApp *GraphApp;

int RequestHostCommand(Session *session,char *name);
class RequestHostHandler : public ServerCommand{
   int handler(Session *session,Packet *input){
      UsersPack *data=(UsersPack*)input;
      QtList* list=(QtList*)GraphApp->current->get_action(RequestListObject);
      QtNotice *notice=(QtNotice*)GraphApp->current->get(LoginNoticeObject);
      char *name_from=data->get_name();
      for(int i=0;i<(int)list->labels.size();i++){
         Label *label=(Label*)(list->labels[i]);
         if(!strcmp(name_from,label->text)){
            notice->add("double request",2,ActionColor);
            return 0;
         }
      }
      notice->add("get request",2,ChooseColor);
      list->add(new Label(coord(0,0),coord(0,0),16,data->get_name()));
      return 0;
   }
};
int ResponceHostCommand(Klient *klient,char *name);
class ResponceHostHandler : public ServerCommand{
   Klient *klient;
   public:
      ResponceHostHandler(Klient *klient_) : klient(klient_){}
   int handler(Session *session,Packet *input){
      QtNotice *notice=(QtNotice*)GraphApp->current->get(LoginNoticeObject);
      UsersPack *data=(UsersPack*)input;
      ResponceHostPack *pack=(ResponceHostPack*)(data->get_packet()->data);
      QtList* list=(QtList*)GraphApp->current->get_action(ConnectListObject);
      if(pack->key==-1){
         notice->add("error request",2,ActionColor);
         return 0;
      }
      notice->add("suc request",2,ChooseColor);
      Connection *con=new Connection(pack,false);
      klient->add_pcon(data->get_name(),con);
      klient->add_valid_key(data->get_name(),con->pack.key);
      list->add(new Label(coord(0,0),coord(0,0),16,data->get_name()));
      return 0;
   }
};

#endif
