

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>

#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAXSZ 100
int main()
{
 int sockfd;
 struct sockaddr_in serverAddress;
 int n;
 char msg1[MAXSZ];
 char msg2[MAXSZ];
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=inet_addr(SERVER_IP);
 serverAddress.sin_port=htons(PORT);
 connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));
 while(1)
 {
  printf("\nEnter Message:\n");
  fgets(msg1,MAXSZ,stdin);
  if(msg1[0]=='#')
   break;
  n=strlen(msg1)+1;
  send(sockfd,msg1,n,0);
 }
 return 0;
}
