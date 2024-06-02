/*File "my_packet.cpp" create by debial, (Вт 14 мар 2023 22:44:23)*/
#ifndef DEBIAL_MY_PACKET_H_SENTURY
#define DEBIAL_MY_PACKET_H_SENTURY
#include <sys/socket.h>

#include"../../general/packet/packet.h"
//то что приходит по этому пакету на сервер и клиент
//Server - Client - Host
enum PacketTypes{
   LoginSuccess,
   LoginPacket,//Login - bool
   RegPacket,//Login - bool
   ErrorPacket,//dont have server handler
   UsersPacket,
   //UsersPacket only for user -> server -> user2
   MsgUserPacket,
   RequestHostPacket,
   ResponceHostPacket,
   ConnectHostPacket,
   FinalResponseHostPacket,
   //ProcPacket
   RequestProcPacket,
   ResponceProcPacket,
   CloseConnectionPacket,
};
enum ErrorTypes{
   Normal = 0,
   RegError,
   UnknownPacket,
   NotLogged,
   IncorectLogin ,
   UserOffline,
   LoginUsed = 19,
   DoubleLogin,
   //ksk error
   MeToMeMessage,
   DoubleRequestUser
};

struct Login{
   char name[16];
   char pass[16];
   Login(char *name_,char *pass_);
   Login(){}
};

struct UsersPack : Packet{
   UsersPack(unsigned char type_,int size_,char *data_,char *name_);
   Packet *get_packet();
   char *get_name();
   virtual ~UsersPack();
};

struct KeyPack : Packet{
   KeyPack(unsigned char type_,int size_,char *data_,int key);
   int get_key();
   char *get_packet();
};

struct MsgPack{
   char str[32];
};

struct ResponceHostPack{
   int key;
   sockaddr addr;
};
struct Error{
   ErrorTypes error;
   Error(ErrorTypes error_) :error(error_) {}
};
#endif
