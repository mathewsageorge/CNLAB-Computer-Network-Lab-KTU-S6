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
    int serverSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;

    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Socket creation failed\n");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Bind failed\n");
        exit(1);
    }

    int clientLen = sizeof(clientAddr);
    int bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientLen);
    buffer[bytesRead] = '\0';
    printf("Client: %s\n", buffer);

    int len = strlen(buffer);
    for (int i = 0; i < len / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[len - i - 1];
        buffer[len - i - 1] = temp;
    }

    sendto(serverSocket, buffer, strlen(buffer), 0, (const struct sockaddr*)&clientAddr, clientLen);
    printf("Response sent.\n");

    return 0;
}