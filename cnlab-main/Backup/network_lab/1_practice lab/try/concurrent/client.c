#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
void main(int argc,char* argv[])
{
	if(argc<3)
	{
		printf("provide address and port to client");
	}
	int sockfd,len;
	struct sockaddr_in server;
	char buffer[1024]={0};
	char* msg="Hello from client";
	len=sizeof(server);
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<=0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
	if(connect(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	sendto(sockfd,msg,strlen(msg),MSG_CONFIRM,(struct sockaddr*)&server,len);
	recvfrom(sockfd,buffer,sizeof(buffer),MSG_WAITALL,(struct sockaddr*)&server,&len);
	printf("Server : %s\n",buffer);
}
