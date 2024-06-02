#include "../../general/session/session.h"
#include "ServerBase.h"
#include <asm-generic/errno-base.h>
#include <bits/types/struct_timeval.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>
#include <sys/select.h>
#include "../../database/dhandler.h"


#include "../handler_command/command.h"
void ServerBase::set_handler(ServerHandler *handler){
   Handler=handler;
}
Session *ServerBase::Listen(){
//loop:
   sockaddr_in addr;
   int len=sizeof(addr);
   int s=accept(sock,(sockaddr*)&addr,(socklen_t*)&len);
   if(s<0){
      //если что либо прервало системный вызов то мы повторяем слушанье
      //тут рекурсия
      if(errno==EINTR) this->Listen();
      //if(errno==EINTR) goto loop; //а тут прыжок
      else error("error accept");
   }
   return new Session(s,&addr,0);
}
ServerBase::operator int(){
   return sock;
}
ServerBase::ServerBase(const char *ip,int port,int queue,InputHandler *handler_input,ServerHandler *handler_) 
   : InternetBase(handler_input,handler_),count(0),sock(ip,port){
   if(listen(sock,queue)==-1) error("error start listen");
   memset(clientfd,-1,FD_SETSIZE*sizeof(int));
   stdinput=2;
   FD_ZERO(&fdset);
   FD_SET((int)sock, &fdset);
   FD_SET(stdinput, &fdset);
   maxfd=((int)sock>stdinput ? (int)sock : stdinput);
   stdflag=false;
}

void ServerBase::Close(){
   for(int i=0;i<=countfd;i++){
      if(clientfd[i]==-1) continue;
      close(clientfd[i]);
      delete clientses[i];
      //FD_CLR(clientfd[i],&fdset);
      printf("succeful close connection %d\n",clientfd[i]);
      clientfd[i]=-1;
   }
   printf("close all connection\n");
   FD_CLR((int)sock, &fdset);
   close((int)sock);
   printf("close Listen socket\n");
}

bool ServerBase::CloseConnection(int id){
   if(Handler->CloseHandler!=0)
      Handler->CloseHandler->handler(clientses[id],NULL);
   close(clientfd[id]);
   delete clientses[id];
   FD_CLR(clientfd[id],&fdset);
   printf("succeful close connection %d\n",clientfd[id]);
   clientfd[id]=-1;
   return true;
}

int ServerBase::add_session(Session *session){
      int i,socket=(int)*session;
      for(i=0;i<FD_SETSIZE;i++){
         if(clientfd[i]==-1){
            clientfd[i]=socket;
            clientses[i]=session;
            session->pos=i;
            break;
         }
      }
      if(i==FD_SETSIZE) error("to many children\n");
      FD_SET(socket,&fdset);
      if(maxfd<socket) maxfd=socket;
      if(i>countfd) countfd=i;
      return i;
}
int ServerBase::handler(){
   fdset_ret=fdset;
   int nready=select(maxfd+2,&fdset_ret,NULL,NULL,NULL);
   if(nready==-1){
      if(errno==EINTR) return 0;
   }
   if(FD_ISSET((int)sock, &fdset_ret)){
      Session *session=Listen();
      int i=add_session(session);
      if(Handler->ConnectHandler!=0 && Handler->ConnectHandler->handler(session,NULL)==1){
         CloseConnection(i);
         printf(" -request ConnectFunc\n");
      }
      if(--nready<=0) return 0;
   }     
   if(FD_ISSET(stdinput, &fdset_ret)){
      Ihandler->handler();
   }
   for(int i=0;i<=countfd;i++,nready--){
      if(FD_ISSET(clientfd[i], &fdset_ret)){
         Packet *packet=clientses[i]->Read();
         if(packet!=NULL){
            try{
               Handler->handler(clientses[i],packet);
            }catch(BinaryTree<unsigned char,ServerCommand*>::NoneFind error){
               printf("get non find packet %d\n",error.key);
            }
            continue;
         }
         CloseConnection(i);
      }
   }
   return 0;
}
