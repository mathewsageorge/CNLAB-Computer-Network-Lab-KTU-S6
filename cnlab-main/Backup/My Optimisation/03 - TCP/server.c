#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int opt = 1, clientLen = sizeof(clientAddr);
    
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("Error: Socket Creation");
        exit(1);
    }

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        printf("Error: Set Socket Option");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(3333);

    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error: Binding");
        exit(1);
    }

    if (listen(serverSocket, 3) < 0) {
        printf("Error: Listen");
        exit(1);
    }

    if ((clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &clientLen)) < 0) {
        printf("Error: Accept");
        exit(1);
    }

    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("Client: %s", buffer);

    char* response = "Message From Server\n";
    send(clientSocket, response, strlen(response), 0);
    printf("\nResponse Sent to Client\n");

    close(serverSocket);
    close(clientSocket);
    return 0;
}