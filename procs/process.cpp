/*File "process.cpp" create by debial, (Сб 01 апр 2023 16:31:26)*/
#include "process.h"
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#define MAX_PATH_SIZE 13 //13 = len "/proc/" len "/statm"
short ChangesType[9]={0,sizeof(long),sizeof(long)*2,
   sizeof(long)*3,sizeof(long)*4,
   sizeof(long)*5,sizeof(long)*6,
   sizeof(long)*7,sizeof(long)*7+sizeof(long long)};
unsigned char ChangesTypeSize[9]={1,sizeof(long),sizeof(long),sizeof(long),sizeof(long),sizeof(long),sizeof(long long),17};

RWerror::RWerror(int errno_,int fd_) : merrno(errno_), fd(fd_){}
void RWerror::info(){
   printf("RW error fd=%d errno %d",fd,merrno);
}
ssize_t Write(int fd,const void *buf,size_t size){
   ssize_t n;
   if((n=write(fd,buf,size))<0){
      RWerror error(fd,errno);
      throw error;
   }
   return n;
}
ssize_t Read(int fd,void *buf,size_t size){
   ssize_t n;
   if((n=read(fd,buf,size))<0){
      RWerror error(fd,errno);
      throw error;
   }
   return n;
}

void DataChanges::set(ChangesTypeList type_,char* data_) {
   type = type_;
   if(data_==NULL) printf("input data == NULL\n");
   if(data!=NULL) delete data;
   unsigned char size=ChangesTypeSize[type_];
   data=new char[size];
   memcpy(data,data_,size);
}
void DataChanges::send(int fd){
   write(fd,&type,sizeof(type));
   write(fd,data,ChangesTypeSize[(int)type]);
}
void DataChanges::get(int fd){
   read(fd,&type,sizeof(type));
   data=new char[ChangesTypeSize[(int)type]];
   read(fd,data,ChangesTypeSize[(int)type]);
}
DataChanges::~DataChanges(){delete [] data;}

Process::Process(const char *pid_str) : status(0),pid(0),parent(0),RmSize(0),VmSize(0),ticks(0),name("null"),ticks_ps(0),del(false),changes_n(0){
   f_size=MAX_PATH_SIZE+strlen(pid_str);
   sscanf(pid_str,"%ld",&pid);
   filename=new char[f_size];
   snprintf(filename,f_size,"/proc/%s/stat",pid_str);
   for(int i=0;i<9;i++) changes[i].type=-1;
}
Process::Process(long pid_) 
   : status(0),pid(pid_),parent(0),RmSize(0),VmSize(0),ticks(0),name("null"),ticks_ps(0),filename(NULL),changes_n(0){}
Process::~Process(){
   if(filename!=NULL)
      delete [] filename;
}
void Process::send(int fd){
   write(fd,&changes_n,sizeof(changes_n));
   changes_n=0;
   for(int i=0;i<9;i++){
      if(changes[i].type!=-1) changes[i].send(fd);
      changes[i].type=-1;
   }
}
void Process::get(int fd){
   for(int i=0;i<9;i++){
      if(changes[i].data!=NULL) delete [] changes[i].data;
      changes[i].type=-1;
   }
   char changes_n_c;
   read(fd,&changes_n_c,sizeof(changes_n));
   for(int i=0;i<changes_n_c;i++){
      changes[i].get(fd);
      set_change((ChangesTypeList)changes[i].type, changes[i].data,true);
   }
   changes_n=changes_n_c;
}
void Process::set_change(ChangesTypeList type,char *data,bool change){
   char *me_data=&status+ChangesType[type];
   unsigned char size=(type==ChangeName ? strlen(me_data) : ChangesTypeSize[type]);
   if(memcmp(me_data,data,size)!=0){
      update=true;
      memcpy(me_data,data,ChangesTypeSize[type]);
      if(!change){
         changes[type].set(type,data);
         changes_n++;
      }
   }else changes[type].type=-1;
   del=false;
}
void Process::info(){
   printf("%s:\npid %ld status %c\nmemory: RmSize %lf VmSize %lf SHmSize %lf RmSize-SHmSize %lf\nprocces: ticks: %llu/%ld parent %ld\n",
         name,pid,status,to_mb(RmSize),to_mb(VmSize),to_mb(SHmSize),
         to_mb(RmSize-SHmSize),ticks,sysconf(_SC_CLK_TCK),parent);
}

CPU* CPU::CreateCpu(FILE *file){
   CPU *cpu=new CPU();
   if(cpu->update(file)) return cpu;
   delete cpu;
   return NULL;
}
bool CPU::update(FILE *file){
   char buf[3];
   long user_=0,nice_=0,system_=0,idle_=0,iowait_=0,irq_=0,softirq_=0;
   if(fread(buf,1,1,file)==0 || buf[0]!='c') return false;
   fscanf(file,"%*s %ld %ld %ld %ld %ld %ld %ld ",&user_,&nice_,&system_,&idle_,&iowait_,&irq_,&softirq_);
   long all_=user_+nice_+system_+irq_+softirq_+idle_;
   long all_p=user+nice+system+irq+softirq+idle;
   if(all_-all_p>5){
      user=user_-user;nice=nice_-nice;system=system_-system;idle=idle_-idle;iowait=iowait_-iowait;irq=irq_-irq;softirq=softirq_-softirq;
   }
   short b;
   while((b=fgetc(file))!='\n' && b!=EOF && b!=0);
   return true;
}
void CPU::info(){
   long load=user+nice+system+irq+softirq;
   long all=load+idle;
   printf(": %ld %ld %ld %ld %ld %ld %ld\nfree %lf%%\n",user,nice,system,idle,iowait,irq,softirq,(double)((double)idle/(double)all)*100);
}
void CPU::send(int fd){
   write(fd,&user,sizeof(long));
   write(fd,&nice,sizeof(long));
   write(fd,&system,sizeof(long));
   write(fd,&idle,sizeof(long));
   write(fd,&iowait,sizeof(long));
   write(fd,&irq,sizeof(long));
   write(fd,&softirq,sizeof(long));
}
void CPU::get(int fd){
   read(fd,&user,sizeof(long));
   read(fd,&nice,sizeof(long));
   read(fd,&system,sizeof(long));
   read(fd,&idle,sizeof(long));
   read(fd,&iowait,sizeof(long));
   read(fd,&irq,sizeof(long));
   read(fd,&softirq,sizeof(long));
}
long long CPU::time_sum(){
   return user+nice+system+idle+iowait+irq+softirq;
}
bool parse_process(Process *process){
   int size=process->f_size;
   process->filename[size-2]=0;
   FILE *stat = fopen(process->filename, "r");
   if(stat==NULL) return false;
   char name[25];
   char status;
   long parent,RmSize,
        VmSize,SHmSize;
   unsigned long long ticks;
   fscanf(stat,"%*d %s %c %ld %*d %*d %*d %*d %*d %*d %*d %*d %*d %*u %llu",
        name,&status,&parent,&ticks);
   name[strlen(name)-1]=0;
   fclose(stat);
   process->filename[size-2]='m';
   stat = fopen(process->filename, "r");
   if(stat==NULL) return false;
   fscanf(stat,"%ld %ld %ld",&VmSize,&RmSize,&SHmSize);
   fclose(stat);
   process->set_change(ChangeName, name+1);
   process->set_change(ChangeStatus, &status);
   process->set_change(ChangeParent, (char*)&parent);
   process->set_change(ChangeVmSize, (char*)&VmSize);
   process->set_change(ChangeRmSize, (char*)&RmSize);
   process->set_change(ChangeSHmSize, (char*)&SHmSize);
   if(process->ticks_ps==0) process->ticks_ps=ticks;
   else{
      unsigned long long ticks_c;
      ticks_c=ticks-process->ticks_ps;
      process->ticks_ps=ticks;
      process->set_change(ChangeTicks,(char*)&ticks_c);
   }
   return true;
}

