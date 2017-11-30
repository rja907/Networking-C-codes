#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>

#define PORT 8000
#define MAXSZ 100
int main()
{
 int sockfd;
 int newsockfd;
 struct sockaddr_in serverAddress;
 struct sockaddr_in clientAddress;
 int n;
 char msg[MAXSZ];
 int clientAddressLength;
 int pid;
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
 serverAddress.sin_port=htons(PORT);
 bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));
 listen(sockfd,5);
 int counter=0;
 while(1)
 {
  printf("\n*****server waiting for new client connection:*****\n");
  clientAddressLength=sizeof(clientAddress);
  newsockfd=accept(sockfd,(struct sockaddr*)&clientAddress,&clientAddressLength); 
  counter++;
  printf("Parent Server accepted request from client: %d\n",counter);
  pid=fork();
  if(pid==0)
  {
    printf("Child Server processing request of client: %d\n",counter);
   while(1)
   {
    n=recv(newsockfd,msg,MAXSZ,0);
    if(n==0)
    {
     close(newsockfd);
     break;
    }
printf("Message (of client %d): %s",counter, msg);
    msg[n]=0;
    }
  exit(0);
  }
  else
  {
   close(newsockfd);
  }
 }
 return 0;
}

