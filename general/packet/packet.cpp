/*File "packet.cpp" create by debial, (Пт 03 фев 2023 13:38:45)*/
#include "packet.h"
#include <string.h>
Packet::Packet(){
   data=NULL;
}
Packet::Packet(unsigned char type_,unsigned int size_,char *data_){
   type=type_;
   size=size_;
   data = new char[size];
   memcpy(data,data_,size);
}
