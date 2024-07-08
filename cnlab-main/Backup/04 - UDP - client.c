#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int clientSocket;
    char buffer[1024];
    char* message = "Hello from client";
    struct sockaddr_in serverAddr;

    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Socket creation failed\n");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    sendto(clientSocket, message, strlen(message), 0, (const struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Message sent.\n");

    int serverLen = sizeof(serverAddr);
    int bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, &serverLen);
    buffer[bytesRead] = '\0';
    printf("Server: %s\n", buffer);

    close(clientSocket);

    return 0;
}