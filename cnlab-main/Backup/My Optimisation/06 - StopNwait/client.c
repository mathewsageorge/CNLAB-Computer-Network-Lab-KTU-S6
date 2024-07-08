#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct frame {
    int frame_kind, sq_no, ack;
    char data[1024];
} Frame;

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
    serverAddr.sin_port = htons(6666);

    int frame_id = 0, ack_recv = 1;
    Frame frame_send, frame_recv;

    while (1) {
        if (ack_recv == 1) {
            frame_send.sq_no = frame_id;
            frame_send.frame_kind = 1;
            frame_send.ack = 0;

            printf("Enter Data: ");
            scanf("%s", frame_send.data);
            sendto(clientSocket, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&serverAddr, serverLen);
            printf("Frame Sent\n");
        }

        int f_recv_size = recvfrom(clientSocket, &frame_recv, sizeof(frame_recv), 0, (struct sockaddr*)&serverAddr, &serverLen);

        if (f_recv_size > 0 && frame_recv.sq_no == 0 && frame_recv.ack == frame_id + 1) {
            printf("Ack Received\n");
            ack_recv = 1;
        } else {
            printf("Ack Not Received\n");
            ack_recv = 0;
        }
        frame_id++;
    }

    close(clientSocket);
    return 0;
}