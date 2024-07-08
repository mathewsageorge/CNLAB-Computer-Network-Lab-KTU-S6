#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct frame {
    int frame_kind, sq_no, ack;
    char data[1024];
} Frame;

int main() {
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientLen = sizeof(clientAddr);

    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Error: Socket Creation");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(6666);

    if (bind(serverSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error: Binding");
        exit(1);
    }

    int frame_id = 0;
    Frame frame_recv, frame_send;

    while (1) {
        int f_recv_size = recvfrom(serverSocket, &frame_recv, sizeof(Frame), 0, (struct sockaddr*)&clientAddr, &clientLen);
        if (f_recv_size > 0 && frame_recv.frame_kind == 1 && frame_recv.sq_no == frame_id) {
            printf("Frame Received: %s\n", frame_recv.data);

            frame_send.sq_no = 0;
            frame_send.frame_kind = 0;
            frame_send.ack = frame_recv.sq_no + 1;

            sendto(serverSocket, &frame_send, sizeof(frame_send), 0, (struct sockaddr*)&clientAddr, clientLen);
            printf("Ack Sent\n");

        } else {
            printf("Frame Not Received\n");
        }
        frame_id++;
    }

    close(serverSocket);
    return 0;
}