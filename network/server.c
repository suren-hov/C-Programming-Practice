#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#define PORT_NUMBER 12345
#define BUFFER_SIZE 1024

void myError(const char* msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // TCP server
    if (sockfd < 0) {
        myError("Invalid socket");
    }

    struct sockaddr_in server_addr, client_addr;
    memset((char*) &server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT_NUMBER);

    int result_bind = bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if (result_bind < 0) {
        myError("Invalid bind");
    }

    listen(sockfd, 3);

    socklen_t client_size = sizeof(client_addr);
    int clientfd = accept(sockfd, (struct sockaddr*) &client_addr, &client_size);
    if (clientfd < 0) {
        myError("Invalid accept");
    }

    char buffer[BUFFER_SIZE];
    int Rbytes = read(clientfd, buffer, BUFFER_SIZE);
    if (Rbytes < 0) {
        myError("Invalid read");
    }

    printf("Message from parent: %s\n", buffer);
    const char* msg = "Good";
    int Wbyte = write(clientfd, msg, strlen(msg));
    if (Wbyte < 0) {
        myError("Invalid write");
    }

    close(clientfd);
}