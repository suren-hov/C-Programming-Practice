#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024
#define ADDR "127.0.0.1"

void myError(const char* msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) {
        myError("Invalid socket");
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ADDR);
    server.sin_port = htons(PORT);


    int connect_result = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
    if (connect_result) {
        myError("Invalid connect");
    }

    char msg[] = "Message that should be sent";
    int Wbytes = send(sockfd, msg, strlen(msg), 0);
    if (send < 0) {
        myError("Invalid send");
    }

    char buffer[BUFFER_SIZE];
    int rBytes = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (rBytes < 0) {
        myError("invalid recv");
    }

    printf("the backward connection is good");
    close(sockfd);
}