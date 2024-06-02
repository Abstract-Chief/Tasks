/*File "dhandler.cpp" create by debial, (Ср 22 фев 2023 14:23:06)*/
#include "database.h"
#define DATABASE_NAME "database/database.db"
#define TABLE_NAME "users"
#include "dhandler.h"

User::User(char *name_,char *pass_,int ip_) : ip(ip_){
   if(name_==NULL) err(1,"null name user\n");
   memcpy(name,name_,16);
   if(pass_!=NULL) memcpy(pass,pass_,16);
}
User::User(char *name_) : ip(0){
   if(name_==NULL) err(1,"null name user\n");
      memcpy(name,name_,32);
}

class UsersTable : public Table {
   public:
   User *user;
   virtual void parser(int argc,char **argv,char** cols){
      if(user==NULL)
         user=new User();
      user->name[0]=0;user->pass[0]=0;
      for(;argc;cols++,argv++,argc--){
         if(!strcmp(*cols,"name")) {memcpy(user->name,*argv,32);}
         else if(!strcmp(*cols,"pass")) {memcpy(user->pass,*argv,32);}
         else if(!strcmp(*cols,"ip")) {sscanf(*argv, "%d", &(user->ip));}
      }
   }
   void print(){
      printf("user %s: %s\n",user->name,user->pass);
   }
};

Database database(DATABASE_NAME);

void restore_online(){
   char command[256];
   sprintf(command,"UPDATE users SET online=-1;");
   database.exec(command);
}
int add_user(const User *user){
   char command[256];
   sprintf(command,"INSERT INTO users (name,pass,ip) VALUES ('%s','%s','%d');",user->name,user->pass,user->ip);
   return database.exec(command);
}
bool get_user(User *user){
   char command[256];
   sprintf(command,"SELECT * FROM users WHERE name='%s';",user->name);
   UsersTable*table=new UsersTable();
   table->user=user;
   return database.select(command, table);
}
bool check_user(const User *user){
   char command[256];
   sprintf(command,"SELECT name FROM users WHERE name='%s' AND pass='%s';",user->name,user->pass);
   UsersTable*table=new UsersTable();
   database.select(command, table);
   return table->user!=NULL;
}
int delete_user(const User *user){
   char command[256];
   sprintf(command,"DELETE FROM users WHERE name='%s',pass='%s';",user->name,user->pass);
   return database.exec(command);
}
