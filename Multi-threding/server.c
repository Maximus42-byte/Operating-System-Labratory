#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
 
int main(){ 
  char buffer[256]; 
  char buffer2[256]; 
  char buffer1[256]; 
  int socket1, portNo, clientLength; 
  int acceptedSocket; 
   
  // defining a host entity to store information of server 
  struct hostent * server;   
  char ipv4[32]; 
  sprintf(ipv4,"127.0.0.1"); 
 
  // initializing address for server entity 
  server=gethostbyname(ipv4);     
 
  // server_address = explicit address of server 
    //client_address = client information 
  struct sockaddr_in server_address, client_address ;   
  clientLength=sizeof(client_address); 
   
  portNo=6000;  // server listens to this port number 
   
  // making socket family = AF_INET, type = SOCK_STREAM , protocol = TCP 
  socket1=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);     
 
  //initializing server addres 
  server_address.sin_family=AF_INET;     
  server_address.sin_port=htons(portNo); 
  server_address.sin_addr.s_addr=INADDR_ANY; 
   
  //binding socket to server address 
  bind ( socket1, (struct sockaddr*) &server_address,sizeof(server_address));
//listening to incoming requests from clients 
  //backlog(maximum number of connections per second) = 5 
  listen(socket1,5); 
 
   
  acceptedSocket = accept(  socket1, (struct sockaddr * )&client_address,&clientLength); 
  bzero(buffer,256); 
  int n; 
  int sum;
char sumstring[256];
    bzero(sumstring,256); 
  while(1) 
  { 
sum =0;
    read(acceptedSocket, buffer, 256); 
    read(acceptedSocket, buffer2, 256); 
    sum = atoi(buffer) + atoi(buffer2);
    printf("[%s@%d]# %s & %s\n", ipv4, portNo,buffer , buffer2 );
    sprintf(sumstring,"%d",sum);
    write(acceptedSocket,sumstring,strlen(sumstring));
    bzero(buffer,256); 
    bzero(buffer2,256); 
    bzero(sumstring,256); 
    sleep(1); 
  } 
  return 0; 
}
