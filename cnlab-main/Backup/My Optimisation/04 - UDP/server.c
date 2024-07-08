#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientLen = sizeof(clientAddr);

    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Error: Socket Creation");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(4444);

    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error: Binding");
        exit(1);
    }

    char buffer[1024];
    int bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr *) &clientAddr, &clientLen);
    buffer[bytesRead] = '\0';
    printf("Client: %s", buffer);

    char* response = "Message From Server";
    sendto(serverSocket, response, strlen(response), 0, (struct sockaddr *) &clientAddr, clientLen);
    printf("\nResponse Sent to Client\n");

    return 0;
}