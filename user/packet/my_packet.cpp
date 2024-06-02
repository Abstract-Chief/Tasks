/*File "my_packet.cpp" create by debial, (Вт 14 мар 2023 22:44:09)*/
#include "my_packet.h"
//!!!!!!!!!!!!!!!!!!!!!!!!!
//никогда сука не передавай сюда 0 никогда
//!!!!!!!!!!!!!!!!!!!!!!!!!
Login::Login(char *name_,char *pass_){
   memcpy(name,name_,32);
   memcpy(pass,pass_,32);
}
UsersPack::UsersPack(unsigned char type_,int size_,char *data_,char *name_){
   type=UsersPacket;
   size=size_+32+1+1;//name size + type(1) + '\0'
   data=new char[size];
   data[0]=type_;
   memcpy(data+1,name_,32);
   data[33]=0;
   memcpy(data+34,data_,size_);
}
Packet *UsersPack::get_packet(){
   Packet *packet=new Packet;
   packet->type=data[0];
   packet->size=size-34;
   packet->data=data+34;
   return packet;
}
char *UsersPack::get_name(){
   return data+1;
}
UsersPack::~UsersPack(){
   if(data!=NULL)
   delete [] data;
}
KeyPack::KeyPack(unsigned char type_,int size_,char *data_,int key_){
   type=type_;
   size=size_+sizeof(key_);
   data=new char[size];
   memcpy(data,&key_,sizeof(key_));
   memcpy(data+sizeof(key_),data_,size_);
}
int KeyPack::get_key(){
   int key=0;
   memcpy(&key,data,sizeof(key));
   return key;
}
char *KeyPack::get_packet(){
   return (data+sizeof(int));
}
