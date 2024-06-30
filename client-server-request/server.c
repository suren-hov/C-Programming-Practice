#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>

#define PORT_NUMBER 8081
#define BUFFER_SIZE 1024
#define SA struct sockaddr 

struct fileParams {
  int fileSize;
  int NumberOfCharacters;
  int NumberOfLines;
  int NumberOfWords;
} fileParam;

void throwError(const char* msg)
{
    perror(msg);
    exit(1);
}

void reciveFileName(int connfd)
{
  char buff[BUFFER_SIZE];
  int n = 0;

  bzero(buff, BUFFER_SIZE); 

  // read the filename from client and save it in buffer 
  read(connfd, buff, sizeof(buff)); 

  // print buffer which contains the client contents 
  printf("File name is: %s\n", buff);

  FILE *file = fopen(buff, "r");
  if (file == NULL)
  {
    throwError("Error opening file");
    exit(EXIT_FAILURE);
  }
  
  fclose(file);
  bzero(buff, BUFFER_SIZE); 

  write(connfd, &fileParam, sizeof(struct fileParams)); 
}

int main()
{
    int sockfd, connfd;
    socklen_t len; 

   sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1){
		  throwError("Socket creation failed...\n"); 
    } else {
  		printf("Socket successfully created..\n"); 
    } 
    
    struct sockaddr_in server_addr, cli;
    bzero(&server_addr, sizeof(server_addr)); 

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = PORT_NUMBER;

    if (bind(sockfd, (SA*) &server_addr, sizeof(server_addr)) < 0)
        throwError("Socket bind failed...\n");
    else
		printf("Socket successfully binded..\n"); 

    if (listen(sockfd, 3) != 0)
        throwError("Listen failed...\n");
    else
		printf("Server listening..\n"); 

  	len = sizeof(cli); 

    connfd = accept(sockfd, (SA*) &cli, &len);
    if (connfd < 0) { 
      throwError("Server accept failed...\n"); 
    } else
      printf("Server accept the client...\n"); 

    reciveFileName(connfd);
  	close(sockfd); 
}