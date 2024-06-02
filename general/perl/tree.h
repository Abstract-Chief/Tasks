//File "tree.cpp" create by debial, (Вс 27 ноя 2022 18:55:12)*/
#ifndef TREE_H_SENTURY
#define TREE_H_SENTURY
#include <stdio.h>
#include <iostream>
using namespace std;
template<class ID_T,class DATA_T>
class BinaryTree{
   struct Block{
      ID_T id;
      DATA_T data;
      Block *r,*l;
      Block(ID_T id_,DATA_T data_,Block *l_=0,Block *r_=0) : id(id_),data(data_),r(r_),l(l_){}
   };

   Block *s;
   int (*handler)(const ID_T,const ID_T);
   
   Block** find_block(Block **ptr,const ID_T &id){
      if(*ptr==0) return ptr;
      char flag=handler(id,(*ptr)->id);
      Block** ptr_c;

      if(flag<0) ptr_c=&(*ptr)->l;
      else if(flag==0) return ptr;
      else ptr_c=&(*ptr)->r;
      return find_block(ptr_c,id);
   }
   void delete_block(Block** ptr){
      if(*ptr==0) return;
      delete_block(&(*ptr)->l);
      delete_block(&(*ptr)->r);
      delete (*ptr);
      *ptr=NULL;
   }
   public:
   class NoneFind{
      public:
      const ID_T &key;
      NoneFind(const ID_T &key_) : key(key_){}
      void info(){
         cerr << "error NullKey key=";
         cerr << key << endl;
      }
   };
   BinaryTree(int (*handler_func)(const ID_T,const ID_T)) 
      : s(0),handler(handler_func){}    
   void add(const ID_T &id,const DATA_T &data){
      *find_block(&s, id)=new Block(id,data);
   }
   void addnl(const ID_T id,const DATA_T data){
      *find_block(&s, id)=new Block(id,data);
   }
   bool check(const ID_T &id){
      return (*find_block(&s,id)==NULL ? false : true);
   }
   DATA_T get(ID_T &id){
      Block *block=*find_block(&s,id);
      return (block ? block->data : throw NoneFind(id));
   }
   DATA_T getnl(const ID_T id){
      Block *block=*find_block(&s,id);
      return (block ? block->data : throw NoneFind(id));
   }
   bool del(const ID_T &id){
      if(check(id)==false) return false;
      delete_block(find_block(&s,id));  
      return true;
   }
};
#endif

