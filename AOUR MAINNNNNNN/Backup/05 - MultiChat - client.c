#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 4444
#define BUFFER_SIZE 2000

int main() {
    struct sockaddr_in serverAddr;
    int clientSocket;
    char buffer[BUFFER_SIZE];
    char *serverAddress = "127.0.0.1"; 

    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket!\n");
        exit(1);
    }
    printf("Socket created...\n");

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverAddress);
    serverAddr.sin_port = htons(PORT);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error connecting to the server!\n");
        exit(1);
    }
    printf("Connected to the server...\n");

    printf("Enter your message: ");
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        if ((send(clientSocket, buffer, BUFFER_SIZE, 0)) < 0) {
            printf("Error sending data!\n\t-%s", buffer);
        }
        if ((recv(clientSocket, buffer, BUFFER_SIZE, 0)) < 0) {
            printf("Error receiving data!\n");
        } else {
            printf("Received: %s\n", buffer);
        }
    }

    close(clientSocket);
    return 0;
}