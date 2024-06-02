/*File "comnand.cpp" create by debial, (Вс 05 мар 2023 22:09:39)*/
#include "command.h"
#include "../../user/packet/my_packet.h"
#include "../../user/session/my_session.h"
#include "../../database/dhandler.h"
#include "../module/ServerBase.h"

int ConnectHandler(Session *session){
   printf("ConnectHandler-> ip: [%s] port: [%d]\n",session->getip(),session->getport());
   session->storage=new LoginStorage();
   return 0;
}

void KlientError(Session *session,ErrorTypes error){
   printf("klient error %d\n",error);
   Packet packet(ErrorPacket,sizeof(Error),(char*)&error);
   session->Send(&packet);
}
int RegServerCommand::handler(Session *session,Packet *input){
   Login *data=(Login*)(input->data);
   printf("reg user name: %s pass:%s ip: %s\n",data->name,data->pass,session->getip());
   User user(data->name,data->pass,session->getip_int());
   ErrorTypes result=(ErrorTypes)add_user(&user);
   if(result>0){
      if(result==19) KlientError(session,LoginUsed);
      else KlientError(session,RegError);
      return 0;
   }
   printf("success reg\n");
   LoginStorage *storage=(LoginStorage*)session->storage;
   storage->login=true;
   storage->set_name(data->name);
   server->login(data->name,session->pos);
   Packet packet(LoginSuccess,1,(char*)&storage->login);
   session->Send(&packet);
   return 0;
}
int LoginServerCommand::handler(Session *session,Packet *input){
   Login *data=(Login*)(input->data);
   User user(data->name,data->pass,session->getip_int());
   printf("try login user name:%s pass:%s ip: %s\n",user.name,user.pass,session->getip());
   ErrorTypes result=(ErrorTypes)!check_user(&user);
   if(result>0){
      KlientError(session, IncorectLogin);
      return 0;
   }
   short res=server->get_login(user.name);
   if(res>=0){
      KlientError(session, DoubleLogin);
      return 0;
   }
   printf("success login\n");
   LoginStorage *storage=(LoginStorage*)session->storage;
   storage->login=true;
   server->login(data->name,session->pos);
   storage->set_name(data->name);
   Packet packet(LoginSuccess,1,(char*)&storage->login);
   session->Send(&packet);
   return 0;
}
int UsersServerCommand::handler(Session *session, Packet *input){
   UsersPack *data=(UsersPack*)(input);
   Packet *packet=data->get_packet();
   LoginStorage *storage=(LoginStorage*)session->storage;
   if(!storage->login){
      KlientError(session, NotLogged);
   }
   if(!strcmp(storage->name,data->get_name())){
      KlientError(session, MeToMeMessage);
      return 0;
   }
   printf("msg{from %s to %s}size=%d\n",storage->name,data->get_name(),packet->size);
   if(server->Handler->check(packet->type) || packet->type==ErrorPacket){
      printf("msg blocked ServerCommandType %d\n",packet->type);
      return 0;
   }
   short result=server->get_login(data->get_name());
   printf("result %d\n",result);
   if(result<0){
      KlientError(session, UserOffline);
      return 0;
   }
   char *name=data->get_name();
   memcpy(name,storage->name,sizeof(storage->name));
   data->type=packet->type;
   server->clientses[result]->Send(data);
   return 0;  
}


