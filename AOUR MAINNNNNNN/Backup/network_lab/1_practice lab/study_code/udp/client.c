#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAXLINE 1024
// Driver code
void main() {
int sockfd;
char buffer[MAXLINE]={0};
char *hello = "Hello from client";
struct sockaddr_in servaddr;
// Creating socket file descriptor
if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
// Filling server information
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(PORT);
servaddr.sin_addr.s_addr = INADDR_ANY;
int n, len;
sendto(sockfd,hello, strlen(hello),MSG_CONFIRM, (struct sockaddr *) &servaddr,sizeof(servaddr));
printf("Hello message sent.\n");
n = recvfrom(sockfd,buffer, MAXLINE,MSG_WAITALL, (struct sockaddr*) &servaddr,&len);
printf("Server : %s\n", buffer);
}



