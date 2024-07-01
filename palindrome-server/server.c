#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#define SA struct sockaddr 

#define PORT_NUMBER 6000
#define BUFFER_SIZE 1024

void throwError(const char* msg) 
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int checkPalindrome(int buff)
{
    int number =buff, result, sum = 0, temp;    
    temp = number;    
    while(number > 0)    
    {
        result = number % 10;    
        sum = (sum * 10) + result;    
        number = number / 10;    
    }    
    return temp==sum;    
}

void recieveNumber(int connfd) {
    int buff = 0;

    recv(connfd, &buff, sizeof(buff), 0); 
    int result = checkPalindrome(buff);

    send(connfd, &result, sizeof(result), 0);
}

int main()
{
    int sockfd, connfd;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
            throwError("Invalid socket");
    }

    struct sockaddr_in server_addr, cli;
    bzero(&server_addr, sizeof(server_addr)); 

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = PORT_NUMBER;

    if (bind(sockfd, (SA*) &server_addr, sizeof(server_addr)) < 0) {
        throwError("Invalid bind");
    }

    if (listen(sockfd, 3) != 0) {
        throwError("Listen failed");
    }

    len = sizeof(cli);

    connfd = accept(sockfd, (SA*) &cli, &len);
    if (connfd < 0) {
        throwError("Connection failed");
    }

    recieveNumber(connfd);
    close(sockfd);
}