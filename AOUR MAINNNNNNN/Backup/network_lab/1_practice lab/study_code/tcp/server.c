#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#define PORT 8080
void main()
{
	int server_fd,new_socket,valread;
	struct sockaddr_in address;
	int opt=1;
	int addrlen=sizeof(address);
	char buffer[1024]={0};
	char* hello = "Hello from server";
	char clientAddr[100];
	if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0)
	{
		exit(EXIT_FAILURE);
	}
	if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	address.sin_port=htons(PORT);
	if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0)
	{
		perror("Bind Failed");
		exit(EXIT_FAILURE);
	}
	if(listen(server_fd,3)<0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if((new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	inet_ntop(AF_INET, &(address.sin_addr), clientAddr, 100);
	valread=read(new_socket,buffer,1024);
	printf("%s : %s\n",clientAddr,buffer);
	send(new_socket,hello,strlen(hello),0);
	printf("Hello message send to client\n");
}

