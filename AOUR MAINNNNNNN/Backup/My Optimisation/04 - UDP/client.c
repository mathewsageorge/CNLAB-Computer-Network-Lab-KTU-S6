#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    int serverLen = sizeof(serverAddr);

    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Error: Socket Creation");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(4444);

    char* message = "Message from Client";
    sendto(clientSocket, message, strlen(message), 0, (struct sockaddr *) &serverAddr, serverLen);
    printf("Message Send to Server\n");

    char buffer[1024];
    int bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr *) &serverAddr, &serverLen);
    buffer[bytesRead] = '\0';
    printf("Server: %s\n", buffer);

    close(clientSocket);
    return 0;
}