#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <arpa/inet.h>
struct packet
{ 
	int data;
	int seq;
};
struct ackn
{
	int seq;
	int ack;
};
void main()
{
	int sender,len,wind,j,l,k,c,i,r,n;
	struct ackn a;
	char buffer[1024];
	struct packet p[25];
	struct sockaddr_in receiver;
	sender=socket(AF_INET,SOCK_STREAM,0);
	receiver.sin_family=AF_INET;
	receiver.sin_port=htons(2069);
	receiver.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sender,(struct sockaddr*)&receiver,sizeof(receiver));
	send(sender,"hai",strlen("hai"),0);
	i=read(sender,buffer,1024);
	buffer[i]='\0';
	printf("Received %s\n",buffer);
	j=1;
	l=1;
	k=1;
	printf("Sending frame \nNo: of frames=8\nWindow size=4\n");
	while(j<=8)
	{ 
		printf("Enter frame data : ");
		scanf("%d",&p[j].data);
		p[j].seq=j;
		j++;
	}
	while(l<=4)
	{ 
		send(sender,(char*)&p[l],sizeof(p[l]),0);
		printf("sending packet with data %d and seq no %d\n",p[l].data,p[l].seq);
		l++;
	} 
	c=0;
	n=8;
	while(c<8)
	{
		r=read(sender,(char *)&a,sizeof(a));
		if (a.ack==1)
		{ 
			c=c+1;
			printf("received ack for packet %d\n",a.seq);
			if(l<=8)
			{
				printf("sending packet with data %d and seq no %d\n",p[l].data,p[l].seq);
				send(sender,(char*)&p[l],sizeof(p[l]),0);
				l++;
			}
		}
		else if (a.ack==-1)
		{ 
			printf("\n\ntime expired for packet %d\n",a.seq);
			printf("resending packet with data %d and seq no %d\n",p[a.seq].data,a.seq);
			send(sender,(char*)&p[a.seq],sizeof(p[a.seq]),0);
		}
	}
	close(sender);
}
