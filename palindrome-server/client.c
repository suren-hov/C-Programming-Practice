#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define PORT_NUMBER 6000
#define BUFFER_SIZE 1024
#define IP_ADDRESS "192.168.34.36"
#define SA struct sockaddr

void throwError(const char* msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
		throwError("Socket creation failed...\n");
	} else
		printf("Socket successfully created..\n");  

    memset((void*)&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    servaddr.sin_port = PORT_NUMBER;

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		throwError("Connection with the server failed...\n");
	} else
		printf("Connected to the server..\n");    

    int number = 0;
    printf("Enter the number: ");
    scanf("%d", &number);

    send(sockfd, &number, sizeof(number), 0);
    int buf = 0;

    recv(sockfd, &buf, BUFFER_SIZE, 0);
  	printf("File number is palindrome: %d\n", buf);

    close(sockfd);
}