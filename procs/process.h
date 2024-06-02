/*File "process.cpp" create by debial, (Сб 01 апр 2023 16:31:26)*/
#ifndef DEBIAL_PROCESS_H_SENTURY
#define DEBIAL_PROCESS_H_SENTURY
#include <cstring>
#include <stdio.h>
#include <unistd.h>
enum ChangesTypeList{
   ChangeStatus=0,
   ChangePid,
   ChangeParent,
   ChangeRmSize,
   ChangeVmSize,
   ChangeSHmSize,
   ChangeTicks,
   ChangeName,
};

class RWerror{
   int merrno,fd;
   public:
   RWerror(int errno,int fd);
   void info();
};

ssize_t Write(int fd,const void *buf,size_t size);
ssize_t Read(int fd,const void *buf,size_t size);

class InetData{
   public:
   virtual void send(int fd) = 0;
   virtual void get(int fd) = 0;
   virtual ~InetData(){}
};

class DataChanges : InetData{ 
   public:
   char type;
   char *data;
   DataChanges() : data(NULL){}
   ~DataChanges();
   void set(ChangesTypeList type_,char* data_);
   void send(int fd);
   void get(int fd);
};

class Process : public InetData{
   //dont touch v
   public:
   char status;
   long pid;
   long parent,
        RmSize,//resident memmory
        VmSize,//virtual memmory
        SHmSize;//shared memmory
   unsigned long long ticks;
   char name[18];
   //dont touch ^
   double to_mb(double page){
      return (page*4)/(1024);
   }
   public:
   unsigned long long ticks_ps;
   char* filename;
   int f_size;
   bool update,del;
   char changes_n;
   DataChanges changes[9];
   Process(const char *pid_str);
   Process(long pid);
   ~Process();
   void set_change(ChangesTypeList type,char *data,bool change=false);
   void info();
   void send(int fd);
   void get(int fd);
};

class CPU : public InetData{
   public:
   static CPU* CreateCpu(FILE *file);
   long user,nice,system,idle,iowait,irq,softirq;
   bool update(FILE *file);
   void info();
   void send(int fd);
   void get(int fd);
   long long time_sum();
};
bool parse_process(Process *process);
#endif
