#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<strings.h>
void main()
{
  struct sockaddr_in serv;
  int cl;
  char msg[101];
  cl=socket(AF_INET,SOCK_STREAM,0);
  bzero(&serv,sizeof(serv));
  serv.sin_family=AF_INET;
  serv.sin_port=htons(5000);
  inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr.s_addr);
  connect(cl,(struct sockaddr*)&serv,sizeof(serv));
  printf("Connected Successfully\n");
  while(1)
  {
     gets(msg);
     write(cl,msg,101);
     read(cl,msg,101);
     printf("Message received from the server : \n");
     puts(msg);
  }
}