/*File "dhandler.cpp" create by debial, (Ср 22 фев 2023 14:23:06)*/
#ifndef DEBIAL_DHANDLER_H_SENTURY
#define DEBIAL_DHANDLER_H_SENTURY
#include <stdio.h>
#include <string.h>
#include <err.h>
//#include "../general/packet/packet.h"

struct User{
   char name[16];
   char pass[16];
   int ip;
   User(){}
   User(char *name_,char *pass_,int ip_);
   User(char *name_);
};
int add_user(const User *user);
bool get_user(User *user);

void restore_online();

bool check_user(const User *user);
int delete_user(const User *user);
#endif
