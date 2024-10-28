//9427993
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<netdb.h>

int main(){
        char buffer[256];
        char buffer1[256];
        int socket1,portNo,clientLength;
        int acceptedSocket;
        struct hostent * server;
        char ipv4[32];
        sprintf(ipv4,"127.0.0.1");
        server=gethostbyname(ipv4);
        struct sockaddr_in server_address,client_address;
        clientLength=sizeof(client_address);
        portNo=8003;
        socket1=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        server_address.sin_family=AF_INET;
       server_address.sin_family=AF_INET;
        server_address.sin_port=htons(portNo);
        server_address.sin_addr.s_addr=INADDR_ANY;
	//binding socket to server address
        bind ( socket1, (struct sockaddr*) &server_address,sizeof(server_address));
	//listening to incoming requests from clients
	//backlog(maximum number of connections per second) = 7
        listen(socket1,5);
        acceptedSocket = accept( socket1,(struct sockaddr * )&client_address,           &clientLength);
        int n;
        int sumi;
        char sums[256];

        while(1)
                {
                read(acceptedSocket, buffer, 256);
                read(acceptedSocket, buffer1,256);
	//      printf("salam");
                sumi=atoi(buffer)+atoi(buffer1);
                sprintf(sums,"%d",sumi);
		write(acceptedSocket,sums,strlen(sums));
                printf("ersal passokh\n");
                bzero(buffer,256);
                bzero(buffer1,256);
                bzero(sums,256);
                sleep(1);
                }
return 0;
}

