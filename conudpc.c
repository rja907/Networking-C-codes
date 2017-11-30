
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int servSocket, portNum, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  servSocket = socket(PF_INET, SOCK_DGRAM, 0);
 
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;
   connect(servSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr));

  while(1){
    printf("Enter your message:\n");
    fgets(buffer,1024,stdin);

    nBytes = strlen(buffer) + 1;
    

    send(servSocket,buffer,nBytes,0);

    printf("Received from server:\n hi");
    nBytes = recv(servSocket,buffer,1024,0);

  

  }

  return 0;
}