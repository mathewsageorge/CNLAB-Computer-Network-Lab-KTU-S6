#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("Error: Socket Creation");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(3333);

    if (connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error: Establishing Connection");
        exit(1);
    }

    char* message = "Message from Client";
    send(clientSocket, message, strlen(message), 0);
    printf("Message Send to Server\n");

    char buffer[1024];
    read(clientSocket, buffer, sizeof(buffer));
    printf("Server: %s", buffer);

    close(clientSocket);
    return 0;
}