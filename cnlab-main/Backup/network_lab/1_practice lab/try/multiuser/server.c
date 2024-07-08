#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
void main()
{
	int sockfd,newsockfd,opt=1,len;
	struct sockaddr_in server,client;
	char buffer[1024]={0};
	char address[100]={0};
	pid_t childpid;	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<=0)
	{
		perror("Socket");
		exit(EXIT_FAILURE);
	}
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(2020);
	server.sin_addr.s_addr=INADDR_ANY;
	len=sizeof(server);
	if(bind(sockfd,(struct sockaddr*)&server,len)<0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

		if(listen(sockfd,3)<0)
		{
			perror("listen");
			exit(EXIT_FAILURE);
		}
	while(1)
	{
		if((newsockfd=accept(sockfd,(struct sockaddr*)&client,&len))<=0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		inet_ntop(AF_INET,(struct sockaddr*)&client.sin_addr,address,100);
		if((childpid=fork())==0)
		{
			close(sockfd);
			while(1)
			{
				recv(newsockfd,buffer,sizeof(buffer),0);
				printf("Message from %s : %s\n",address,buffer);
				send(newsockfd,buffer,strlen(buffer),0);
				printf("Reply to %s : %s\n",address,buffer);
			}
		}
		close(newsockfd);
	}
}
