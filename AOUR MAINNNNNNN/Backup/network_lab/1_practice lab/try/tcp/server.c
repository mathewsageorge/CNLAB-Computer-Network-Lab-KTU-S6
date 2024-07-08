#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define PORT 8080

void main()
{
	int sockfd,opt=1,length;
	char buffer[1024]={0};
	char* msg="Hello from server";
	struct sockaddr_in server;
	length=sizeof(length);
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<=0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=INADDR_ANY;
	if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	if(listen(sockfd,3)<0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if((sockfd=accept(sockfd,(struct sockaddr*)&server,(socklen_t*)&length))<=0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	read(sockfd,buffer,sizeof(buffer));
	printf("Client : %s\n",buffer);
	send(sockfd,msg,strlen(msg),0);
	printf("Message replied to client\n");
}

