/*File "parser.cpp" create by debial, (Чт 06 апр 2023 15:45:44)*/
#ifndef DEBIAL_PARSER_H_SENTURY
#define DEBIAL_PARSER_H_SENTURY
#include "process.h"

#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include<stdexcept>

class ProcessParser : public InetData{
   std::vector<CPU*> cpu;
   std::unordered_map<long,Process*> process;
   bool type;
   time_t update_time;
   void set_ticks(){
      ticks=0;
      for(unsigned long i=0;i<cpu.size();i++){
         ticks+=cpu[i]->time_sum();
      }
   }
   void update_process(const char *pids);
   void update();
   public:
   unsigned long long ticks;
   std::vector<long> del_process;
   std::vector<long> add_process;
   ProcessParser(bool server);
   ~ProcessParser();
   void clear();
   void info();
   void send(int fd);
   void get(int fd);
   const std::unordered_map<long,Process*> get_processes(){
      return process;
   }
};

#endif
