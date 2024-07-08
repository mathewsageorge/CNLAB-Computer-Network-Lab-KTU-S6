#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PORT 8080

void main()
{
	int sockfd,length;
	char buffer[1024]={0};
	char* msg="Hello from server";
	struct sockaddr_in server;
	length=sizeof(server);
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<=0)
	{
		perror("socket");
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
	recvfrom(sockfd,buffer,sizeof(buffer),MSG_WAITALL,(struct sockaddr*)&server,&length);
	printf("Client : %s\n",buffer);
	sendto(sockfd,msg,strlen(msg),MSG_CONFIRM,(struct sockaddr*)&server,length);
	printf("Message sent to client\n");
}
