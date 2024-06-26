#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define PORT_NUMBER 12345
#define IP_ADDRESS "127.0.0.1"
#define BUFFER_SIZE 1024

void myError(const char* msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0) {
        myError("Invalid socket");
    }

    struct sockaddr_in server;
    memset((void*)&server, 0, sizeof(server));

    server.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_NUMBER);

    int connectResult = connect(clientfd, (struct sockaddr*) &server, sizeof(server));
    if (connectResult < 0) {
        myError("Invalid connect");
    }

    const char* msg = "Message from Client\n";
    int Wbytes = write(clientfd, msg, strlen(msg));
    if (Wbytes < 0) {
        myError("Invalid write");
    }

    char buffer[BUFFER_SIZE];
    int Rbytes = read(clientfd, buffer, BUFFER_SIZE);
    if (Rbytes < 0) {
        myError("Invalid read");
    }    

    close(clientfd);
}
