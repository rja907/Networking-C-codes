#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
  int udpSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;


  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  


  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));


  addr_size = sizeof serverStorage;

  while(1){
    
    nBytes = recv(udpSocket,buffer,1024,0);

    printf("Message received: %s", buffer);
    printf("Enter message to send: ");
    scanf("%s",buffer);
    send(udpSocket,buffer,1024,0);
  }

  return 0;
}