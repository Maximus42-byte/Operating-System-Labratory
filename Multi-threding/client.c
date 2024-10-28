#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <netdb.h> 
 
int main() 
{ 
  char buffer[256]; 
  char buffer2[256]; 
  int socket1, portNo; 
  struct hostent * server; 
  char ipv4[32]; 
  sprintf(ipv4,"127.0.0.1"); 
  server=gethostbyname(ipv4); 
   
  struct sockaddr_in server_address; 
  portNo=6000; 
  socket1=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
   
  server_address.sin_family=AF_INET; 
  server_address.sin_port=htons(portNo); 
  bcopy((char *)server->h_addr,(char *)&server_address.sin_addr.s_addr,server->h_length); 
  connect(socket1,(struct sockaddr *)&server_address,sizeof(server_address)); 
  sprintf(buffer,"message from client");
int a,b; 
char lastbuffer[256];
  while(1) 
  { 
scanf("%d",&a);
scanf("%d",&b);
  sprintf(buffer,"%d",a);
  sprintf(buffer2,"%d",b);
    write(socket1,buffer,strlen(buffer));
    write(socket1,buffer2,strlen(buffer2));
    read(socket1, lastbuffer, 256); 
    printf("%d\n", atoi(lastbuffer) );
    bzero(buffer,256); 
    bzero(buffer2,256); 
    bzero(lastbuffer,256);
    sleep(1); 
  } 
  return 0; 
}
