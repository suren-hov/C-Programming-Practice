#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define REQUEST_SIZE 1024
#define IP "127.0.0.1"
#define PORT 8080

void error(char*);
int createIPv4socket(void);
void handleRequest(int, char*);
struct sockaddr_in* createIPv4Address(char*, int);