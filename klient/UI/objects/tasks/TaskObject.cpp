/*File "TaskObject.cpp" create by debial, (Пт 14 апр 2023 18:49:56)*/
#include "TaskObject.h"
//CPUInfo::CPUInfo(std::vector<CPU*> *cpu_,coord pos,coord size) : QtObject(pos,size),cpu(cpu_){
      //int N=cpu->size()-1;
      //int cols=1;
      //if(N%4==0)cols=4;
      //else if(N%2==0)cols=2;
      //coord gpos(pos);
      //coord one_size((size.x-(N-1))/N,(size.y-(N-1))/N);
      //char number[3];
      //memset(number,0,sizeof(number));
      //for(int i=0;i<N;i++){
         //for(int j=0;j<cols;j++,i++){
            //if(i>999) err(1,"вы конченый?\n");
            //sprintf(number,"%d",i+1);
            //graphick_cpu.push_back(new InfoProgressBar(gpos,one_size,number));
            //gpos.x+=one_size.x+1;
         //}
         //gpos.y+=one_size.y+1;
      //}
   //}
//void CPUInfo::graphick(float x_res,float y_res){
   //for(auto it=graphick_cpu.begin();it!=graphick_cpu.end();it++)
      //(*it)->graphick(x_res, y_res);
//}
ProccentLabel::ProccentLabel(coord pos,coord size,bool type_) 
   : QtObject(pos,size),bar(pos,size),type(type_){
}
void ProccentLabel::graphick(float x,float y){
   bar.percent=percent;
   mvprintw(pos.y*x,pos.x*x,"%.1f%%",percent);
   if(type){
      bar.set_pos(coord(pos.x*x+5,pos.y*y),coord(size.x*x-3,size.y));
      mvprintw(pos.y*y,pos.x*x+2+size.x*x,"|");
      bar.graphick(1,1);
   }
}
ProcessInfo::ProcessInfo(Process *process,unsigned long long *all_ticks_,coord pos,coord size) 
   : QtObject(pos,size),all_ticks(all_ticks_){
   name=process->name;
   status=&process->status;
   pid=&process->pid;
   parent=&process->parent;
   RmSize=&process->RmSize;
   VmSize=&process->VmSize;
   SHmSize=&process->SHmSize;
   ticks=&process->ticks;
   name_label=new Label(coord(0,0),coord(16,1),16,NULL);
   name_label->text=name;
   cpu=new ProccentLabel(coord(0,0),coord(4,1),true);
   mem=new ProccentLabel(coord(0,0),coord(4,1),true);
}
void ProcessInfo::graphick(float x,float y){
   coord n_pos(pos.x*x,pos.y*y),n_size(size.x*x,size.y*y);
   int cur=0;

   mvprintw(n_pos.y, n_pos.x,"%c %ld",*status,*pid);//теоретически максимум 19 фактически 6 :=
   cur+=9;
   name_label->set_pos(coord(n_pos.x+cur,n_pos.y),coord((n_size.x-cur>16 ? 16 : n_size.x-cur),1));
   name_label->graphick(1,1);
   cur+=17;
   if(cur>n_size.x) return;
   int ost=n_size.x-cur;
   if(all_ticks!=0)
      cpu->percent=((double)(*ticks)/(double)(*all_ticks))*100;
   if(ost>=12){
      int s=n_pos.x+cur+(ost-9)/2;
      ost-=12;
      cpu->set_pos(coord(s,n_pos.y),coord(4+ost/2,1));
      mem->set_pos(coord(s+7+ost/2,n_pos.y),coord(4+ost/2,1));
      cpu->graphick(1,1);
      mem->graphick(1,1);
   }else if(ost>=5){
      cpu->set_pos(coord(n_pos.x+cur+(ost-4)/2,n_pos.y),coord(4,1));
      cpu->graphick(1,1);
   }
}

ConnectionList::ConnectionList(coord pos, coord size, int heigh,QtObjectHandler *handler,const char *text_,char acolor,char pcolor) 
   : QtList(coord(pos.x+1,pos.y+2),coord(size.x-2,size.y-3),1,handler,acolor,pcolor)
{
   int len=strlen(text_);
   label_n=new Label(pos,coord(18,1),len+10,NULL);
   rect=new Rectangle(coord(pos.x,pos.y+1),coord(size.x,size.y-1));
   text=new char[len+1];
   memcpy(text,text_,len);
}
void ConnectionList::set_handler(QtObjectHandler *handler_){
   handler=handler_;
}
int ConnectionList::MyHandler(int input){
   if(handler!=NULL) return QtList::MyHandler(input);
   return 0;
}
void ConnectionList::select(bool type_s){
   QtList::select(type_s);
   if(type_s) rect->color=2;
   else rect->color=pcolor;
}
void ConnectionList::graphick(float x_res,float y_res){
   snprintf(label_n->text,18,"%s: %d",text,(int)labels.size());
   label_n->graphick(x_res,y_res);
   rect->graphick(x_res,y_res);
   QtList::graphick(x_res,y_res);
}
ConnectionList::~ConnectionList(){
   delete rect;
   delete label_n;
   delete text;
}
Slider::Slider(coord pos,coord size,char key_,const char *t1,const char *t2,int color_) 
   :  ActionQtObject(this),QtObject(pos,size),color(color_),type(0),key(key_){
   coord block_size(size.x/2,size.y);
   block[0]=new BorderActionLabel(pos,block_size,3,0,t1);
   block[1]=new BorderActionLabel(coord(pos.x+block_size.x,pos.y),block_size,3,0,t2);
}
Slider::Slider(coord pos,coord size,char key_,BorderActionLabel *a_,BorderActionLabel *b_,int color_) 
   :  ActionQtObject(this),QtObject(pos,size),color(color_),type(0),key(key_){
   block[0]=a_;
   block[1]=b_;
}
int Slider::MyHandler(int input){

   block[type]->disactive();
   type=!type;
   block[type]->active();
   return 0;
}
void Slider::select(bool type_s){
   if(type_s) block[type]->active();
   else block[type]->rect.color=color;
}
void Slider::graphick(float x_res,float y_res){
   block[0]->BorderActionLabel::graphick(x_res,y_res);
   block[1]->BorderActionLabel::graphick(x_res,y_res);
}
Slider::~Slider(){
   delete block[0];
   delete block[1];
}
