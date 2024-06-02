/*File "perl.cpp" create by debial, (Вс 05 мар 2023 22:24:11)*/
#include "perl.h"
Perl::Perl(const char *oper) : commands(strcmp),op(oper) {}

void Perl::add_command(const char *command,PerlCommand *parser){
   if(strlen(command)>32) err(1,"oversize command %s\nmax command size = %d",command,32);
   else if(commands.check(command)) err(1,"dublicate command %s\n",command);
   commands.add(command,parser);
   printf("succeful add command\n");
}
char *Perl::read(){
   printf("%s",op);
   buffer[0]='\0';
   fgets(buffer,256,stdin);
   if(buffer[0]=='\0') throw 1;
   return buffer;
}
PerlCommand *Perl::parse(){
   read();
   sscanf(buffer,"%s",command);
   try{
      PerlCommand* result=commands.getnl(command);
      return result->parse(buffer+strlen(command));
   }catch(BinaryTree<const char*,PerlCommand*>::NoneFind error){
      error.info();  
   }
   return NULL;
}
