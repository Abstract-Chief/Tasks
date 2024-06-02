/*File "packet.cpp" create by debial, (Пт 03 фев 2023 13:38:45)*/
#ifndef DEBIAL_PACKET_H_SENTURY
#define DEBIAL_PACKET_H_SENTURY
#include <string.h>
#include <stdlib.h>
struct Packet{
   unsigned char type;
   unsigned short size;
   char *data;
   Packet();
   Packet(unsigned char type,unsigned short size,char *data_);
   virtual ~Packet(){
      if(data!=NULL)
         delete [] data;
   }
};
#endif
