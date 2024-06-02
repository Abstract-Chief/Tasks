/*File "ProcessList.h" create by debial, (Ср 24 мая 2023 16:57:04)*/
#ifndef DEBIAL_PROCESSLIST_H_SENTURY
#define DEBIAL_PROCESSLIST_H_SENTURY
#include "TaskObject.h"

class ProcessList : public QtList{
   public:
   ProcessList(coord pos, coord size,QtObjectHandler *handler) : QtList(pos,size,1,handler){}
   void add_object(Process *process,unsigned long long *all_ticks){
      add(new ProcessInfo(process,all_ticks));
   }
   void del_object(long pid){
      for(auto it=labels.begin();it!=labels.end();it++){
         ProcessInfo *lab=(ProcessInfo*)*it;
         if(*lab->pid==pid){
            labels.erase(it);
            delete lab;
         } 
      }
   }
   void update(ProcessParser *parser){
      std::unordered_map<long, Process*> processes=parser->get_processes();
      std::vector<long> added=parser->add_process;
      std::vector<long> deleted=parser->del_process;
      for(auto it=added.begin();it!=added.end();++it){
         Process *process=processes.at(*it);
         add_object(process,&parser->ticks);
      }
      for(auto it=deleted.begin();it!=deleted.end();++it)
         del_object(*it);
   }
};

#endif
