#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define PORT_NUMBER 8082
#define BUFFER_SIZE 1024
#define IP_ADDRESS "127.0.0.1"
#define SA struct sockaddr

struct fileParams {
  int fileSize;
  int NumberOfCharacters;
  int NumberOfLines;
  int NumberOfWords;
};

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

    char buff[BUFFER_SIZE];
    bzero(buff, sizeof(buff));

    printf("Enter the file name: ");
    int n = 0;

    while ((buff[n++] = getchar()) != '\n');
    write(sockfd, buff, sizeof(buff));

    bzero(buff, sizeof(buff));
    struct fileParams fileParam;

    read(sockfd, &fileParam, sizeof(struct fileParams));

	printf("File size is : %d\n", fileParam.fileSize);
	printf("Number of characters is : %d\n", fileParam.NumberOfCharacters);
	printf("Number of lines is : %d\n", fileParam.NumberOfLines);

    close(sockfd);
}