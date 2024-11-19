#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5001
#define BUFFER_SIZE 1024

int main() {
    int socketFd;
    struct sockaddr_in myaddr, remoteAddr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_size;
    ssize_t recv_len;

    // Create UDP socket
    socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address (Static IP: 127.0.0.1)
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(PORT);
    myaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Static IP for local traffic

    // Bind the socket to the specified IP and port
    if (bind(socketFd, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0) {
        perror("Bind failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }

    printf("UDP server listening on 127.0.0.1:%d\n", PORT);

    while (1) {
        // Clear buffer and receive message
        memset(buffer, 0, BUFFER_SIZE);
        addr_size = sizeof(remoteAddr);
        recv_len = recvfrom(socketFd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&remoteAddr, &addr_size);
        if (recv_len < 0) {
            perror("Receive failed");
            continue;
        }

        // Null-terminate the received string
        buffer[recv_len] = '\0';

        // Display the received message
        printf("Received message: %s\n", buffer);
    }

    // Close the socket (unreachable in this loop, but good practice to include)
    close(socketFd);
    return 0;
}
