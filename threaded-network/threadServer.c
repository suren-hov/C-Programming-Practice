#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 12345
#define BUFFER_SIZE 1024
#define MAX_COUNT 3

int max_Client_count = 0;

void* ClientHandler(void* arg);

void myError(const char* msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        myError("Invalid socket");
    }

    pthread_t threads[MAX_COUNT];
    struct sockaddr_in server, client;
    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    int bind_result = bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    if (bind_result < 0) {
        myError("Invalid bind");
    }

    int listen_result = listen(sockfd, MAX_COUNT);
    if (listen_result < 0) {
        myError("Invalid listen");
    }

    socklen_t client_size = sizeof(client);
    while(1) {
        int clientfd = accept(sockfd, (struct sockaddr*)&client, &client_size);
        if (clientfd < 0) {
            myError("invalid accept");
        }
        
        pthread_create(&threads[max_Client_count], NULL, ClientHandler, (void*)&clientfd);
        max_Client_count++;

        if (max_Client_count >= MAX_COUNT) {
            printf("max count!!!!!!");
            break;
        }
    }

    for (int i = 0; i < max_Client_count; ++i) {
        pthread_detach(threads[i]);
    }
    close(sockfd);
}

void* ClientHandler(void* arg) {
    int clientfd = *((int*)arg);

    char buffer[BUFFER_SIZE];
    int rBytes = recv(clientfd, buffer, BUFFER_SIZE, 0);
    if (rBytes < 0) {
        myError("Invalid recv");
    }

    printf("Message from client %d is %s: \n", clientfd, buffer);

    char msg[] = "Message is received";
    int vbytes = send(clientfd, msg, strlen(msg), 0);
    if (vbytes < 0) {
        myError("Invalid send");
    }
    return NULL;
}