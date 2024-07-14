#include "../includes/sockutils.h"

void error(char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int createIPv4socket(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        error("Creating a Socket.");
    }
    return sockfd;
}

struct sockaddr_in* createIPv4Address(char* ip, int port) { 
    struct sockaddr_in* address = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));

    address->sin_port = htons(port);
    address->sin_family = AF_INET;

    if(!strlen(ip))
        address->sin_addr.s_addr = INADDR_ANY;
    else    
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    return address;
}

void send_response(int client_socket, const char* status, char* content_type, char* content) {
    char buffer[REQUEST_SIZE];
    snprintf(buffer, sizeof(buffer),
        "HTTP/1.1 %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %lu\r\n" 
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status, content_type, strlen(content), content);
    send(client_socket, buffer, strlen(buffer), 0);
}

void handleRequest(int sockfd, char* request) {
    char method[10], path[128], protocol[10];
    if(sscanf(request, "%s %s %s", method, path, protocol) < 3) {
        send_response(sockfd, "405 Method Not Allowed", "text/plain", "Method Not Allowed");
        return;
    }
    if(strcmp(method, "GET") != 0){
        send_response(sockfd, "405 Method Not Allowed", "text/plain", "Method Not Allowed");
        return;
    }
    printf("PATH : %s\n", path);

    FILE* file = fopen(path, "r");
    if(!file) {
        send_response(sockfd, "404 Not Found", "text/plain", "File Not Found");
        return;
    }
    fseek(file, 0, SEEK_END);
    size_t f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buff = (char*)malloc(f_size+1);

    size_t read = fread(buff, 1, f_size, file);
    if(read != f_size) {
        free(buff);
        send_response(sockfd, "500 Internal Server Error", "text/plain", "File Not Found");
        return;
    }
    send_response(sockfd, "200 Success", "text/plain", buff);
    free(buff);
    fclose(file);
}
