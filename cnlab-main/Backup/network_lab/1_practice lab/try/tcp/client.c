#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define PORT 8080

void main()
{
	int sockfd;
	char buffer[1024]={0};
	char* msg="Hello from client";
	struct sockaddr_in client;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<=0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	client.sin_family=AF_INET;
	client.sin_port=htons(PORT);
	if(inet_pton(AF_INET,"127.0.0.1",&client.sin_addr)<=0)
	{
		perror("Address");
		exit(EXIT_FAILURE);
	}
	if(connect(sockfd,(struct sockaddr*)&client,sizeof(client))<0)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	send(sockfd,msg,strlen(msg),0);
	printf("Message sent to server\n");
	read(sockfd,buffer,sizeof(buffer));
	printf("Server : %s\n",buffer);
}
