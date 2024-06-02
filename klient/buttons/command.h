/*File "command.h" create by debial, (Ср 26 апр 2023 14:02:32)*/
#ifndef DEBIAL_BUTTON_COMMAND_H_SENTURY
#define DEBIAL_BUTTON_COMMAND_H_SENTURY

#include "../UI/objects/tasks/TaskObject.h"
#include "../module/BaseKlient.h"
#include "../command/ksk_command.h"
#include "../command/procs_command.h"
#include "../../user/packet/my_packet.h"

class LoginButtonHandler : public ButtonHandler{
   public:
   Session *session;
   bool *type_login;
   char *name,*pass;
   LoginButtonHandler(Session *session_,bool *type,char *name_,char *pass_) 
      : session(session_),type_login(type),name(name_),pass(pass_){}
   int handler(Button *button){
      Login user;
      int l1=strlen(name),l2=strlen(pass);
      if(l1<=1 || l2 <=1) return 0;
      memcpy(user.name,name,l1);
      memcpy(user.pass,pass,l2);
      user.pass[l2]=0;
      Packet packet((*type_login ? RegPacket : LoginPacket ),sizeof(Login),(char*)&user);
      session->Send(&packet);
      return 0;
   }
   
};

class RequestButtonHandler : public ButtonHandler{
   public:
   Session *session;
   char *name;
   RequestButtonHandler(Session *session_,char *name_) 
      : session(session_),name(name_){}
   int handler(Button *button){
      RequestHostCommand(session,name);
      return 0;
   }
   
};

class ConnectionListHandler : public QtObjectHandler{
   GraphickApp *app;
   Klient *klient;
   QtList *list;
   public:
   ConnectionListHandler(GraphickApp *app_,Klient *klient_,QtList *list_) 
      : app(app_),klient(klient_),list(list_) {}
   int handler(QtObject *object,int key){
      Label *label=(Label*)object;
      if(key=='f'){
         Connection *con=klient->get_connection(label->text);
         Session *session=new Session();
         if(con ==NULL || !session->Conect(&con->pack.addr)){
            list->labels.erase(list->labels.begin()+list->current);  
            return 0;
         }
         klient->add_session(session);
         con->session=session;
         int null=1;
         int key=con->pack.key;
         KeyPack pack(RequestProcPacket,sizeof(null),(char*)&null,key);
         session->Send(&pack);
         app->set(TaskScreen);
      }
      if(key=='d'){
         list->labels.erase(list->labels.begin()+list->current);  
         int null=1;
         Packet* msg=new UsersPack(CloseConnectionPacket,sizeof(null),(char*)&null,label->text);
         klient->ks_ses.Send(msg);
      }
      return 0;
   }
};
class ResponseListHandler : public QtObjectHandler{
   public:
   QtList *list;
   Klient *klient;
   char *name;
   ResponseListHandler(Klient *klient_,QtList *list_) 
      : list(list_),klient(klient_){}
   int handler(QtObject *object,int key){
      Label *label=(Label*)object;
      if(key=='f'){
         ResponceHostCommand(klient,label->text);
         list->labels.erase(list->labels.begin()+list->current);  
         delete label;
      }
      else if(key=='d'){
         list->labels.erase(list->labels.begin()+list->current);  
         ResponceHostPack pack;
         pack.key=-1;
         UsersPack msg(ResponceHostPacket,sizeof(pack),(char*)&pack,label->text);
         klient->ks_ses.Send(&msg);
         delete label;
      }
      return 0;
   }
};

#endif
