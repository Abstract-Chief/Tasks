/*File "database.cpp" create by debial, (Ср 22 фев 2023 14:15:17)*/
#ifndef DEBIAL_DATABASE_H_SENTURY
#define DEBIAL_DATABASE_H_SENTURY
#include "iterator.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

class Table{
   public:
   int count;
   virtual void parser(int argc,char **argv,char** cols) = 0;
};
class Database{
   sqlite3* db;

   char *ErrorMessage;
   int result;
   public:
   static int callback_select(void* data, int argc, char** argv, char** azColName);
   Database(const char* name);
   int select(const char *command,Table* table);
   int exec(const char *command);
   ~Database();
};

#endif
