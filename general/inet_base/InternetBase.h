/*File "InternetBase.cpp" create by debial, (Ср 29 мар 2023 12:42:07)*/
#ifndef DEBIAL_INTERNETBASE_H_SENTURY
#define DEBIAL_INTERNETBASE_H_SENTURY
#include "../perl/perl.h"
#include "../../user/session/my_session.h"
#include "../handler/handler.h"
#include "../perl/tree.h"
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <string.h>

//ErrorsApp
enum AppErrorCode{
   
};
class AppErrorCommand{
   public:
   virtual int handler(Session *session,AppErrorCode code) = 0;
};
class InputHandler{
   public:
   virtual void handler() = 0;
};
class InternetBase{
   protected:
   fd_set fdset;
   int stdinput,maxfd;
   bool stdflag;
   public:
   ServerHandler *Handler;
   InputHandler *Ihandler;
   InternetBase(InputHandler *handler_input,ServerHandler *handler_)
      : stdinput(fileno(stdin)),stdflag(false),Handler(handler_),Ihandler(handler_input){}
   virtual int handler() = 0;

};

class InternetApp{
   public:
   BinaryTree<const char *, InternetBase*> handlers;
   BinaryTree<AppErrorCode,AppErrorCommand*> ErrorHandler;
   InternetBase *current;
   InternetApp();
   bool select(const char *name);
   bool add(const char *name,InternetBase *handler);
   bool del(const char *name){
      return handlers.del(name);
   }
   inline int handler(){
      return current->handler();
   }
};

#endif
