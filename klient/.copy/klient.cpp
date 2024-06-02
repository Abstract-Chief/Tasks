#include "session.h"
#include <cstdio>

int main(int argc,char **argv){
   if(argc!=2) return 2;
   Session<String> session(NULL,0);//port == 0 -> system choose port
   session.Conect(argv[1],1223);
   printf("succeful connect\n");
   String send;
   while(1){
      printf("> ");
      scanf( "%s", (char*)send);
      if(!strcmp((char*)send,"exit")) break;
      session.Send(&send);
      String *a=session.Read();
      if(a==NULL) break;
      printf("server: %s\n",(char*)a);
      delete a;
   }
   close(session);
   printf("close conection");
}
