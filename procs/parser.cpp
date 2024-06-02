/*File "parser.cpp" create by debial, (Чт 06 апр 2023 15:45:44)*/
#include "parser.h"
ProcessParser::ProcessParser(bool server) : type(server),update_time(0){
   if(!server) return;
   FILE *file=fopen("/proc/stat","r");
   for(CPU *obj;(obj=CPU::CreateCpu(file))!=NULL;) cpu.push_back(obj);
   fclose(file);
}
ProcessParser::~ProcessParser(){
   for(auto it=process.begin();it!=process.end();it++){
      #if DEBUG
         printf("Debugger: Delete %s\n",it->second->name);
      #endif
      delete it->second;
   }
   for(auto it=cpu.begin();it!=cpu.end();it++) delete (*it);
}
void ProcessParser::update_process(const char *pids){
   if (pids[0] >= '0' && pids[0] <= '9'){
      long pid=0;
      sscanf(pids,"%ld",&pid);
      Process *proc;
      try{
         proc=process.at(pid);
      }catch(const std::out_of_range &err){
         proc=new Process(pids);
         process.insert(std::make_pair(pid,proc));
         #if DEBUG
            printf("Debugger: Add Process %ld\n",pid);
         #endif
      }
      parse_process(proc);
      proc->del=false;
   }
}
void ProcessParser::update(){
   FILE *file=fopen("/proc/stat","r");
   for(unsigned long i=0;i<cpu.size();i++)
      cpu[i]->update(file);
   fclose(file);
   #if DEBUG
      printf("Debugger: update cpu\n");
   #endif
   update_time=time(NULL);
   struct dirent *p;
   DIR *directory=opendir("/proc");
   while ((p = readdir(directory))) update_process(p->d_name);
   closedir(directory);
}
void ProcessParser::clear(){
   #if DEBUG
      int i=0;
   #endif
   for(auto it=process.begin();it!=process.end();++it){
      if(it->second->del==true){
         #if DEBUG
            printf("Debugger: delete %s %d\n",it->second->name,it->second->pid);
            i++;
         #endif
         del_process.push_back(it->second->pid);
         delete it->second;
         process.erase(it->first);
      }else it->second->del=true;
   }
   #if DEBUG
      printf("Debugger: delete %d\n",i);
   #endif
}
void ProcessParser::info(){
   printf("Process %ld\n",process.size());
   clear();
   for(auto it=process.begin();it!=process.end();it++) it->second->info();
   printf("Engine\n");
   for(auto it=cpu.begin();it!=cpu.end();it++) (*it)->info();
}
void ProcessParser::send(int fd){
   //send process
   update();
   clear();
   int count_cpu=cpu.size();
   write(fd,&count_cpu,sizeof(count_cpu));
   for(auto it=cpu.begin();it!=cpu.end();it++)
      (*it)->send(fd);
   #if DEBUG
      printf("Debugger: Sucefull send %d procs\n",count_cpu);
   #endif
   long count_process=process.size();
   int a=0;
   write(fd,&count_process,sizeof(count_process));
   for(auto it=process.begin();it!=process.end();it++){
      #if DEBUG
         printf("Debugger: Send Process %s\n",it->second->name);
      #endif
      write(fd,&it->second->pid,sizeof(long));
      it->second->send(fd);
      a++;
   }
   #if DEBUG
      printf("Debugger: Sucefull send %d %d process\n",count_process,a);
   #endif
   //send deleted
   int count_delp=del_process.size();
   write(fd,&count_delp,sizeof(count_delp));
   for(auto it=del_process.begin();it!=del_process.end();it++){
      write(fd,&(*it),sizeof(*it));
      del_process.erase(it);  
   }
}
void ProcessParser::get(int fd){
   int count_cpu=0;
   read(fd,&count_cpu,sizeof(count_cpu));
   for(int i=0;i<count_cpu;i++){
      CPU *proc;
      if(i>=(int)cpu.size()) proc=new CPU();
      else proc=cpu.at(i);
      proc->get(fd);
      cpu.push_back(proc);
   }
   del_process.clear();
   add_process.clear();
   //read process
   long count_process=0;
   read(fd,&count_process,sizeof(count_process));
   #if DEBUG
      printf("Debugger: try read count_process: %d\n",count_process);
   #endif
   for(long i=0;i<count_process;i++){
      long pid=-1;
      read(fd,&pid,sizeof(pid));
      #if DEBUG
         printf("Debugger: Read pid %ld\n",pid);
      #endif
      try {
         process.at(pid)->get(fd);
      }catch(std::out_of_range &err){
         Process *proc=new Process(pid);
         proc->get(fd);
         process.insert(std::make_pair(pid,proc));
         add_process.push_back(pid);
      }
   }
   //read deleted
   int count_delp;
   read(fd,&count_delp,sizeof(count_delp));
   for(int i=9;i<count_delp;i++){
      long pid;
      read(fd,&pid,sizeof(pid));
      delete process.at(pid);
      process.erase(pid);
      del_process.push_back(pid);
   }
   set_ticks();
}
