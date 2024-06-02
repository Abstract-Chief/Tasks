#include "database.h"

int Database::callback_select(void* data, int argc, char** argv, char** azColName) {
      ((Table*)data)->parser(argc,argv,azColName);
      return 0;
   }
Database::Database(const char* name){
   int rc = sqlite3_open(name, &db);
   if (rc != SQLITE_OK) {
      sqlite3_close(db);
      err(1, "Database: error open %s\n",name);
   }
}
int Database::select(const char *command,Table* table){
   if(table==NULL) err(1,"Database: not found table\n");
   result = sqlite3_exec(db, command,callback_select, table, &ErrorMessage);
   if (result != SQLITE_OK) {
      #if DEBUG
         printf("Debugger: error %s\n",ErrorMessage);
      #endif
      sqlite3_free(ErrorMessage);
      return result;
   }
   return 0;
}
int Database::exec(const char *command){
   result = sqlite3_exec(db,command,NULL, NULL, &ErrorMessage);
   if (result != SQLITE_OK) {
      #if DEBUG
         printf("Debugger: error %s\n",ErrorMessage);
      #endif
      sqlite3_free(ErrorMessage);
      return result;
   }
   return 0;
}
Database::~Database(){
   sqlite3_close(db);
}

//int main() {
   //Database data("database.db");
   //UsersTable table;
   //data.select("SELECT id,name,pass FROM users", &table);
   //table.print();
   //return 0;
//}
