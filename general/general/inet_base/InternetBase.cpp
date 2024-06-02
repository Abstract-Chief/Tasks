/*File "InternetBase.cpp" create by debial, (Ср 29 мар 2023 13:10:45)*/
#include "InternetBase.h"
int function(const AppErrorCode a,const AppErrorCode b){
   if(a>b) return 1;
   else if(a<b) return -1;
   else return 0;
}
InternetApp::InternetApp() : handlers(strcmp),ErrorHandler(function){}
bool InternetApp::select(const char *name){
   if(handlers.check(name)==false) return false;
   current=handlers.get(name);
   return true;
}
bool InternetApp::add(const char *name,InternetBase *handler){
   if(handlers.check(name)==true) return false;
   if(current==NULL) current=handler;
   handlers.add(name, handler);
   return true;
}
