#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#define PORT 8080
void main()
{
	int sock=0,valread;
	struct sockaddr_in serv_addr;
	char buffer[1024]={0};
	char* hello = "Hello from client";
	if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("Socket creation error\n");
		exit(EXIT_FAILURE);
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORT);	
	if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ address not supported\n");
		exit(EXIT_FAILURE);
	}
	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("\nConnection Failed\n");
		exit(EXIT_FAILURE);
	}
	send(sock,hello,strlen(hello),0);
	printf("Hello message sent to server\n");
	valread=read(sock,buffer,1024);
	printf("%s\n",buffer);
}
