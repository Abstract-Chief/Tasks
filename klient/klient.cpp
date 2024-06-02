#include "../general/inet_base/InternetBase.h"
#include <ncurses.h>
#include <sys/socket.h>
#include "UI/app.h"
#include "UI/objects/Notice/notice.h"
#include "config/net_conf.h"
#include "config/ui.h"
#include "config/input_conf.h"
#include <fcntl.h>
#include <sys/ioctl.h>
GraphickApp *GraphApp;


int main(int argc,char **argv){
   if(argc!=2) return 2;

   InternetApp *app=GetInternetApp(argv[1]);
   Klient *klient=(Klient*)app->current;
   GraphApp=GetGraphick(klient,&klient->ks_ses);
   Rectangle rect(coord(20,20),coord(5,5),ActionColor);
   GraphApp->current->add(0,&rect,false);
   app->current->Ihandler=new MyInputHandler(GraphApp);
   if(GraphApp->current==NULL) printf("NULL SCREEN\n");
   while(!app->handler()){
      clear();
      GraphApp->current->render();
      refresh();
   }
   endwin();
   return 0;
}
