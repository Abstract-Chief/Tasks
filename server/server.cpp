/*File "server.cpp" create by debial, (Пт 03 мар 2023 12:29:45)*/
#include "module/ServerBase.h"
#include "handler_command/command.h"
#include "perl_command/command.h"
#include "../user/packet//my_packet.h"
#include "server.h"

class ConnectHandler : public ServerCommand{
   int handler(Session *session,Packet *packet){
      printf("ConnectHandler-> ip: [%s] port: [%d]\n",session->getip(),session->getport());
      session->storage=new LoginStorage();
      return 0;
   }
};
class CloseHandler : public ServerCommand{
   Server *server;
   public:
   CloseHandler(Server *server_) : server(server_) {} 
   int handler(Session *session,Packet *packet){
      LoginStorage *storage=(LoginStorage*)session->storage;
      if(storage->login)
         server->delogin(storage->name);
      return 0;
   }
};

int main(int argc,char **argv){

   Server server(NULL,1223,10,NULL,NULL);
   ServerHandler handler(new ConnectHandler(),new CloseHandler(&server));
   server.set_handler(&handler);
   restore_online();
   handler.add_command(LoginPacket,new LoginServerCommand(&server));
   handler.add_command(RegPacket,new RegServerCommand(&server));
   handler.add_command(UsersPacket,new UsersServerCommand(&server));
   InternetApp app;
   app.add("server",&server);
   while(!app.handler());
   server.Close();
}
