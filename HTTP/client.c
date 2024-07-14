#include "./includes/sockutils.h"
#include "./includes/usage.h"
#include <stdio.h>

#define DESTFILE "tmp.html"

void openInBrowser(char *response) {
    if (strncmp(response, "HTTP/1.1 200", 12) == 0) {
        char *content = strstr(response, "\r\n\r\n");
        if (content) {
            content += 4;
            FILE *dest = fopen(DESTFILE, "w");
            if (!dest)
                error("Unable to create file.");
            fprintf(dest, "%s", content);
            fclose(dest);

            char command[256];
            snprintf(command, sizeof(command), "xdg-open %s", DESTFILE);
            
            if ((system(command)) == -1)
                error("Unable to execute command.");
        } else
            printf("HTML content not found in the response.\n");
    } else
        printf("%s\n", response);
}

int main(int argc, char* argv[]) {
    if(argc < 4) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    char *hostname = argv[1];
    char *filename = argv[2];
    if((strcmp(argv[3], "GET")) != 0)
        error("Method Not Allowed");
    char *method = argv[3];

    int sockfd = createIPv4socket();
    struct sockaddr_in* address = createIPv4Address(IP, PORT);
    char req[REQUEST_SIZE] = {0};

    if((connect(sockfd, (struct sockaddr*)address, sizeof(*address))) < 0) {
        error("Connecting to the Server.");
    }
    printf("[+] Connected to the server : %s:%d \n", IP, PORT);

    snprintf(req, REQUEST_SIZE, "%s %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", method, filename, hostname);

    ssize_t amount_sent = send(sockfd, req, strlen(req), 0);
    if(amount_sent > 0) 
        printf("[+] SENT : %s\n", req);

    char html[4096] = {0};
    ssize_t amount_rcv = recv(sockfd, html, 4096, 0);

    if(amount_rcv > 0) 
        openInBrowser(html);
    
    free(address);
    close(sockfd);
    return 0;
}