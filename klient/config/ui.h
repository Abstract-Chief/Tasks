/*File "ui.cpp" create by debial, (Ср 26 апр 2023 15:22:11)*/
#ifndef DEBIAL_UI_H_SENTURY
#define DEBIAL_UI_H_SENTURY
#include "../UI/app.h"
#include "../module/BaseKlient.h"

GraphickApp* GetGraphick(Klient *klient,Session *session);

enum ObjectsScreen{
   LoginScreen=1,
   CentralScreen,
   TaskScreen,
};

enum LoginObjects{
   LoginHandlerObject,
   LoginNoticeObject,
};

enum CentralObject{
   RequestListObject,
   ConnectListObject,
};

enum TaskObject{
   ProcessListObject,
};
#endif
