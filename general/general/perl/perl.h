// perl.cpp
#ifndef PERL_H_SENTURY
#define PERL_H_SENTURY
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>
#include"tree.h"

class PerlCommand{
   public:
   void check(int argc,int error){
      if(error < argc) printf("erorr in %d arg\n",error+1);
   }
   virtual PerlCommand* parse(const char* input) = 0;
   virtual int handler() = 0;
};


class Perl{
   BinaryTree<const char*,PerlCommand*> commands;
   char buffer[256];
   char command[32];
   const char *op;
   public:
   Perl(const char *oper);
   void add_command(const char *command,PerlCommand *parser);
   char *read();
   PerlCommand *parse();
};
#endif
