#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<strings.h>
#include<stdlib.h>
#include<sys/select.h>
#include<sys/time.h>
#include<errno.h>
void main()
{
  fd_set rset;
  struct sockaddr_in serv,cli;
  pid_t pid;
  int tser,user,cl,count,selre,len,max;
  char msg1[101],msg2[101];
  struct timeval tim;
  tser=socket(AF_INET,SOCK_STREAM,0);
  user=socket(AF_INET,SOCK_DGRAM,0);
  bzero(&serv,sizeof(serv));
  serv.sin_family=AF_INET;
  serv.sin_port=htons(5000);
  serv.sin_addr.s_addr=htonl(INADDR_ANY);
  bind(tser,(struct sockaddr*)&serv,sizeof(serv));
  bind(user,(struct sockaddr*)&serv,sizeof(serv));
  listen(tser,10);
  count=0;
  max=(tser>user)?tser:user;
  max++;
  while(1)
  {
    FD_ZERO(&rset);
   FD_SET(tser,&rset);
   FD_SET(user,&rset);
   tim.tv_sec=10;
   tim.tv_usec=0;
    selre=select(max,&rset,NULL,NULL,&tim);
    if(tser<0)
    {
      if(errno==EINTR)
        continue;
      else
      {
        printf("Error during select");
        exit(0);
      }
    }
    else if(tser==0)
      continue;
    else
   {
     if(FD_ISSET(user,&rset))
    {
      recvfrom(user,msg1,101,0,(struct sockaddr*)&cli,&len);
     printf("Request received from a UDP client : ");
     puts(msg1);
     printf("Enter the message to be sent to the UDP client\n");
     gets(msg1);
     //puts(msg1);
     sendto(user,msg1,101,0,(struct sockaddr*)&cli,sizeof(serv));
     //puts(msg1);
    }
    if(FD_ISSET(tser,&rset))
    {
    cl=accept(tser,(struct sockaddr*)NULL,NULL);
    count++;
    printf("parent server accepted request from : TCP client %d\n",count);
    pid=fork();
    if(pid<0)
    {
      printf("Error during fork");
      exit(0);
    }
    else if(pid==0)
    {
      close(tser);   
      printf("Child server processing request of : TCP client %d\n",count);
      while(1)
      {
       if(read(cl,msg2,101)==0)
         exit(1);
       printf("message from client %d : ",count);
       puts(msg2);
       printf("Enter the message to be sent to the TCP client %d\n", count);
       gets(msg2);
       write(cl,msg2,101);
      }
    }
    else
    {
      close(cl);  
    }
    }
   }
   }
}