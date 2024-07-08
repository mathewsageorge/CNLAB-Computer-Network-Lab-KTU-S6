#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
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
	int receiver,sender,len,c,t,wind,j,l,k,r,ran,f,i,n;
	int opt=1;
	struct ackn a[20];
	char buffer[1024];
	struct packet p[25];
	struct sockaddr_in senderadd,recvadr;
	receiver=socket(AF_INET,SOCK_STREAM,0);
	recvadr.sin_family=AF_INET;
	recvadr.sin_port=htons(2069);
	recvadr.sin_addr.s_addr=inet_addr("127.0.0.1");
	setsockopt(receiver, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt));
	if (bind(receiver,(struct sockaddr*)&recvadr,sizeof(recvadr))<0)
	printf("Not Connected\n");
	listen(receiver,3);
	sender=accept(receiver,(struct sockaddr*)&senderadd,&len);
	i=read(sender,buffer,1024);
	buffer[i]='\0';
	printf("Received %s\n",buffer);
	send(sender,"hello",strlen("hello"),0);
	j=1;
	k=1;
	c=0;
	while(j<=4)
	{ 
		r=read(sender,(char *)&p[j],sizeof(p[j]));
		j++;
	}
	t=4;
	j=1;
	n=8;
	while(c<8)
	{
		ran=rand()%3;
		if(ran==0)
		{ 
			a[j].ack=-1;
			a[j].seq=p[j].seq;
		} 
		else
		{ 
			a[j].ack=1;
			a[j].seq=p[j].seq;
		}
		if(a[j].ack==1)
		{ 
			printf("Received Packet with data %d and seq %d\n",p[j].data,p[j].seq);
			send(sender,(char*)&a[j],sizeof(a[j]),0);c++;j++;
		}
		else
		{ 
			send(sender,(char*)&a[j],sizeof(a[j]),0);
			printf("\n\n");
			j++; 
			n++;
		}
		if(t< n)
		{ 
			t++;
			read(sender,(char*)&p[t],sizeof(p[t])); 
		}
	}
	close(receiver);
}
