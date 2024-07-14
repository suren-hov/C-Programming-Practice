#include "./includes/sockutils.h"

int main() {
    int sockfd = createIPv4socket();
    struct sockaddr_in* address = createIPv4Address("", PORT);

    if((bind(sockfd, (struct sockaddr*)address, sizeof(*address))) < 0) 
        error("Error in binding.");
    if(listen(sockfd, 10) < 0)
        error("Error in listening.");
    printf("[+] Bounded successfully : %s:%d\n", IP, PORT);

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    int acceptedfd = accept(sockfd, (struct sockaddr*)&clientAddress, (socklen_t*)&clientAddressSize);

    char request[1024] = {0};
    ssize_t amount_rcv = recv(acceptedfd, request, 1024, 0);
    if(amount_rcv > 0) {
        printf("Received from Server: %s\n", request);
        handleRequest(acceptedfd, request);
    }

    free(address);
    shutdown(sockfd, SHUT_RDWR);
}