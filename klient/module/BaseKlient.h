/*File "BaseKlient.cpp" create by debial, (Вт 14 мар 2023 23:06:24)*/
#ifndef DEBIAL_BASEKLIENT_H_SENTURY
#define DEBIAL_BASEKLIENT_H_SENTURY
#include<ncurses.h>
#include "../../general/perl/perl.h"
#include "../../user/session/my_session.h"
#include "../../general/handler/handler.h"
#include "../../server/module/ServerBase.h"
#include "../../general/inet_base/InternetBase.h"
#include "../../procs/parser.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unordered_map>
#include <string>

enum ConsoleHostType{
   NothingHost=0,
   GetRequestHost=1,
   CompliteRequest=2,
   CompliteConnect=3
};

struct Connection{
   bool server;
   Session *session;
   ResponceHostPack pack;
   ProcessParser parser;
   Connection(ResponceHostPack *pack,bool server_) : server(server_),session(NULL),pack(*pack),parser(server_){}
};

class Klient : public ServerBase{
   std::unordered_map<std::string,Connection *> connection;
   std::unordered_map<int,std::string> valid_key;
   public:
   Session ks_ses;
   Klient(InputHandler *handler_input,ServerHandler *handler_,char *ip);
   void add_pcon(const char *name,Connection *pack);
   void del_pcon(const char *name);
   void add_valid_key(const char *name,int key);
   void del_valid_key(const char *name);
   bool check_key(int key);
   Connection *get_connection(int key);
   Connection *get_connection(std::string name);
};
#endif
