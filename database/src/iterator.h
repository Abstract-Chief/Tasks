/*File "iterator.h" create by debial, (Ср 22 фев 2023 14:15:43)*/
#ifndef DEBIAL_ITERATOR_H_SENTURY
#define DEBIAL_ITERATOR_H_SENTURY

template<class T>
class Iterator{
   int count;
   struct Block{
      T data;
      Block *next,*prev;
      Block(T data_,Block *prev_=0,Block *next_=0) : data(data_),next(next_),prev(prev_){}
   };
   public:
   Block *s,*e,*iterator;
   Iterator() : s(0),e(0),iterator(0){
      s=e;
   }
   bool next(){
      if(!iterator->next) return 1;
      iterator=iterator->next;
      return 0;
   }
   bool prev(){
      if(iterator==s) return 1;
      iterator=iterator->prev;
      return 0;
   }
   void add(T data){
      if(!s) iterator=s=e=new Block(data);
      else e=e->next=new Block(data,e);
   }
   void del(){
      Block *next=iterator->next;
      Block *prev=iterator->next;
      delete iterator;
      iterator->prev->next=next;
      next->prev=prev;
   }
   void start(){
      iterator=s;
   }
   T get(){
      return iterator->data;
   }
   operator T(){return iterator->data;}
};

#endif
