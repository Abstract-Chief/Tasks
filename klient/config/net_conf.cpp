/*File "net_conf.cpp" create by debial, (Пн 24 апр 2023 17:36:58)*/
#include "net_conf.h"
#include "input_conf.h"
#include "../command/ksk_command.h"
#include "../command/ks_command.h"
#include "../command/procs_command.h"

Klient *GetKlient_Server(InternetApp *app,InputHandler *input,char *ip){
   ServerHandler *klient_handler=new ServerHandler(0,0);
   Klient *klient=new Klient(input,klient_handler,ip);
   klient_handler->add_command(ErrorPacket,new ErrorHandler);
   klient_handler->add_command(LoginSuccess,new LoginCommandHandler);
   klient_handler->add_command(RequestHostPacket,new RequestHostHandler);
   klient_handler->add_command(ResponceHostPacket,new ResponceHostHandler(klient));
   klient_handler->add_command(RequestProcPacket,new RequestProcHandler(klient));
   klient_handler->add_command(ResponceProcPacket,new ResponceProcHandler(klient));
   return klient;
}

InternetApp *GetInternetApp(char *ip){
   InternetApp *app=new InternetApp;
   Klient *klient=GetKlient_Server(app,NULL,ip);
   app->add("klient",klient);
   return app;
}
