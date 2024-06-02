/*File "procs_command.cpp" create by debial, (Ср 24 мая 2023 16:04:52)*/
#include "procs_command.h"

void GetProcCommand(Session *session,int key){
   bool n=false;
   KeyPack packet(RequestProcPacket,sizeof(n),(char*)&n,key);
   session->Send(&packet);
}
