#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("provide port number");
		exit(EXIT_FAILURE);
	}
	int sockfd,len;
	struct sockaddr_in server;
	time_t ct;
	char buffer[1024]={0};
	len=sizeof(server);
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<=0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;
	if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		recvfrom(sockfd,buffer,sizeof(buffer),MSG_WAITALL,(struct sockaddr*)&server,&len);
		ct=time(NULL);
		sprintf(buffer,"%s",ctime(&ct));
		sendto(sockfd,buffer,strlen(buffer),MSG_CONFIRM,(struct sockaddr*)&server,len);
	}
}

