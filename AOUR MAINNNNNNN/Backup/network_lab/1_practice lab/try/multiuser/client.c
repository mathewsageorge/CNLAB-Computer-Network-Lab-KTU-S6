#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
void main(int argc,char* argv[])
{
	int sockfd,opt=1,len;
	struct sockaddr_in server;
	char buffer[1024]={0};
	len=sizeof(server);	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<=0)
	{
		perror("Socket");
		exit(EXIT_FAILURE);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(2020);
	server.sin_addr.s_addr=inet_addr(argv[1]);
	if(connect(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		printf("Enter data : ");
		scanf("%s",buffer);
		send(sockfd,buffer,strlen(buffer),0);
		read(sockfd,buffer,sizeof(buffer));
		printf("Received : %s\n",buffer);
	}
}
