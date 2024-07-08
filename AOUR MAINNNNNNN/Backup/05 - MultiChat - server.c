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
    struct sockaddr_in serverAddr, clientAddr;
    int serverSocket, clientSocket, len;
    char buffer[BUFFER_SIZE];
    pid_t childpid;

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket!\n");
        exit(1);
    }
    printf("Socket created...\n");

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error binding!\n");
        exit(1);
    }
    printf("Binding done...\n");

    if (listen(serverSocket, 5) < 0) {
        printf("Error listening!\n");
        exit(1);
    }
    printf("Waiting for a connection...\n");

    while (1) {
        len = sizeof(clientAddr);
        if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&len)) < 0) {
            printf("Error accepting connection!\n");
            exit(1);
        }
        printf("Connection accepted...\n");

        if ((childpid = fork()) == 0) { 
            close(serverSocket); 
            while (1) {
                memset(buffer, 0, BUFFER_SIZE);
                if ((recv(clientSocket, buffer, BUFFER_SIZE, 0)) < 0) {
                    printf("Error receiving data!\n");
                    exit(1);
                }
                printf("Client: %s\n", buffer);

                if ((send(clientSocket, buffer, BUFFER_SIZE, 0)) < 0) {
                    printf("Error sending data!\n");
                    exit(1);
                }
                printf("Sent: %s\n", buffer);
            }
        }
        close(clientSocket);
    }
    return 0;
}