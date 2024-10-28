//9427993
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
        int socket1, portNo;
        struct hostent * server;
        char ipv4[32];
        sprintf(ipv4,"127.0.0.1");
        server=gethostbyname(ipv4);
        struct sockaddr_in server_address;
        portNo=8003;
        socket1=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        server_address.sin_family=AF_INET;
        server_address.sin_port=htons(portNo);
        bcopy( (char *)server->h_addr,
        (char *)&server_address.sin_addr.s_addr,
	 (char *)&server_address.sin_addr.s_addr,
        server->h_length
        );
        connect(socket1,(struct sockaddr *)&server_address,sizeof(server_address));
        sprintf(buffer,"message from client");
        char buffer1[256];
        char buffer2[256];
        char buf[256];
        int a,b;

        while(1)
                {
                scanf("%d%d",&a,&b);
                sprintf(buffer1,"%d",a);
                sprintf(buffer2,"%d",b);
                write(socket1,buffer1,strlen(buffer1));
                printf("addad ersal shod %s\n",buffer1);
                write(socket1,buffer2,strlen(buffer2));
                printf("addad ersal shod %s\n",buffer2);
		read(socket1,buf,256);
                printf("%d\n",atoi(buf));
                sleep(1);
                bzero(buffer1,256);
                bzero(buffer2,256);
                bzero(buf,256);
                }
        return 0;
        }

