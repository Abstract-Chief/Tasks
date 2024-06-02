/*File "ksk_command.cpp" create by debial, (Пт 05 мая 2023 15:59:32)*/
#include "ksk_command.h"
int RequestHostCommand(Session *session,char *name){
   bool NullData = false;
   Packet* msg=new UsersPack(RequestHostPacket,sizeof(NullData),(char*)&NullData,name);
   session->Send(msg);
   return 0;  
}
int ResponceHostCommand(Klient *klient,char *name){
   ResponceHostPack pack;
   pack.key=(int)((double)RAND_MAX*rand()/(RAND_MAX+(double)1))+100;
   Connection *con=new Connection(&pack,true);
   klient->add_valid_key(name,pack.key);
   klient->add_pcon(name, con);
   socklen_t size = sizeof(pack.addr);
   getsockname(klient->sock, &pack.addr, &size);
   Packet* msg=new UsersPack(ResponceHostPacket,sizeof(pack),(char*)&pack,name);
   klient->ks_ses.Send(msg);
   return 0;

}
