/*File "ui.cpp" create by debial, (Ср 26 апр 2023 15:22:11)*/
#include "ui.h"
#include "../buttons/command.h"
#include "../UI/objects/tasks/TaskObject.h"
#include "../UI/objects/tasks/ProcessList.h"
#include "../UI/objects/Notice/notice.h"

Screen* GetLoginScreen(Session *session){
   LoginHandler *login=new LoginHandler(coord(5,5));
   login->button->handler=new LoginButtonHandler(session,&login->slider->type,login->login->text,login->pass->text);
   QtNotice *notice=new QtNotice(coord(COLS-15,0),coord(13,15),5,15);
   Screen *screen=new Screen(stdscr,coord(COLS,LINES));
   screen->add_action(LoginHandlerObject, login,true);
   screen->add(LoginNoticeObject,notice,true);
   return screen;
}

Screen* GetCentralScreen(GraphickApp *app,Klient *klient,Session *session){
   Screen *screen=new Screen(stdscr,coord(COLS,LINES));
   ConnectionList *list_request=new ConnectionList(coord(24,5),coord(18,17),4,NULL,"requests");
   ConnectionList *list_connect=new ConnectionList(coord(5,12),coord(18,10),4,NULL,"connections");

   list_request->set_handler(new ResponseListHandler(klient,list_request));
   list_connect->set_handler(new ConnectionListHandler(app,klient,list_connect));

   EditLabel *elabel=new EditLabel(coord(5,5),coord(18,3),16);
   BorderActionLabel *but_label=new BorderActionLabel(coord(5,8),coord(5,3),7,0,"connect");
   Button *button=new Button(but_label,'f',new RequestButtonHandler(session,elabel->text));
   QtNotice *notice=new QtNotice(coord(COLS-15,0),coord(13,15),5,15);
   elabel->set_action(button,DownDirection);
   button->set_action(list_request,RightDirection,false);
   elabel->set_action(list_request,RightDirection);
   button->set_action(list_connect,DownDirection);
   list_connect->set_action(list_request,RightDirection,false);

   screen->add_action(RequestListObject,list_request,true);
   screen->add_action(ConnectListObject,list_connect,true);
   screen->add(LoginNoticeObject,notice,true);
   screen->add_action(4,button,true);
   screen->add_action(5,elabel,true);
   screen->set_action(5);
   return screen;
}

Screen *GetTaskScreen(){
   Screen *screen=new Screen(stdscr,coord(COLS,LINES));
   ProcessList *list=new ProcessList(coord(5,5),coord(35,15),NULL);
   screen->add_action(ProcessListObject,list,true);
   screen->set_action(ProcessListObject);
   return screen;
}

GraphickApp* GetGraphick(Klient *klient,Session *session){
   GraphickApp *app=new GraphickApp;
   app->add(LoginScreen,GetLoginScreen(session));
   app->add(CentralScreen,GetCentralScreen(app,klient,session));
   app->add(TaskScreen,GetTaskScreen());
   return app;
}
