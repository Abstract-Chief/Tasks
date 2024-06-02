/*File "ks_command.h" create by debial, (Пт 05 мая 2023 15:48:41)*/
#ifndef DEBIAL_KS_COMMAND_H_SENTURY
#define DEBIAL_KS_COMMAND_H_SENTURY

#include "../config/ui.h"
#include "../UI/objects/Notice/notice.h"

extern GraphickApp *GraphApp;

class ErrorHandler : public ServerCommand{
   int handler(Session *session,Packet *input){
      Error *error=((Error*)(input->data));
      QtNotice *notice=(QtNotice*)GraphApp->current->get(LoginNoticeObject);
      char *text=NULL;
      BaseColors color=ActionColor;
      switch (error->error) {
         case Normal:{text=(char*)"Success"; color=ChooseColor;break;}
         case UnknownPacket:{text=(char*)"UnknownPack"; break;}
         case RegError:{text=(char*)"RegError"; break;}
         case NotLogged:{text=(char*)"NotLogged"; break;}
         case IncorectLogin:{text=(char*)"ErrLogin"; break;}
         case LoginUsed:{text=(char*)"LoginUsed"; break;}
         case UserOffline:{text=(char*)"UserOff"; color=PassiveColor;break;}
         case DoubleLogin:{text=(char*)"DoubleLog";color=PassiveColor;break;}
         case MeToMeMessage:{text=(char*)"MeToMe";color=PassiveColor;break;}
         case DoubleRequestUser:{text=(char*)"DoubleReg";break;}
      }
      if(text!=NULL){
         notice->add(text,2,color);
      }
      return 0;
   }
};
class LoginCommandHandler : public ServerCommand{
   int handler(Session *session,Packet *input){
      QtNotice *notice=(QtNotice*)GraphApp->current->get(LoginNoticeObject);
      notice->add("Success Login",2,ChooseColor);
      GraphApp->set(CentralScreen);
      return 0;
   }
};


#endif
