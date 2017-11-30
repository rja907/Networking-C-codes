#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<strings.h>
void main()
{
  struct sockaddr_in serv;
  int cl,len;
  len=sizeof(serv);
  char msg[101];
  cl=socket(AF_INET,SOCK_DGRAM,0);
  bzero(&serv,sizeof(serv));
  serv.sin_family=AF_INET;
  serv.sin_port=htons(5000);
  inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr.s_addr);
  while(1)
  {
     printf("Enter the message:\n");
     gets(msg);
     sendto(cl,msg,101,0,(struct sockaddr*)&serv,sizeof(serv));
     recvfrom(cl,msg,101,0,(struct sockaddr*)&serv,&len);
     printf("Message received from the server: \n");
     puts(msg);
  }
}