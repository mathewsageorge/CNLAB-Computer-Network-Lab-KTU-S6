#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PORT 8080

void main()
{
	int sockfd,length;
	struct sockaddr_in client;
	char buffer[1024]={0};
	char* msg="Hello from client";
	length=sizeof(client);
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<=0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	client.sin_family=AF_INET;
	client.sin_port=htons(PORT);
	if(inet_pton(AF_INET,"127.0.0.1",&client.sin_addr)<=0)
	{
		perror("address");
		exit(EXIT_FAILURE);
	}
	sendto(sockfd,msg,strlen(msg),MSG_CONFIRM,(struct sockaddr*)&client,length);
	printf("Message send to server\n");
	recvfrom(sockfd,buffer,sizeof(buffer),MSG_WAITALL,(struct sockaddr*)&client,&length);
	printf("Server : %s\n",buffer);
}
