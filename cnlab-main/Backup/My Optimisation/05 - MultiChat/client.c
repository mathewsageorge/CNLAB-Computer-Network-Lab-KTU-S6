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
    serverAddr.sin_port = htons(5555);

    if (connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error: Establishing Connection");
        exit(1);
    }

    char buffer[1024];
    while (1) {
        printf("Enter Message: ");
        fgets(buffer, sizeof(buffer), stdin);

        send(clientSocket, buffer, sizeof(buffer), 0);
        recv(clientSocket, buffer, sizeof(buffer), 0);

        printf("Message Send: %s", buffer);
    }

    close(clientSocket);
    return 0;
}