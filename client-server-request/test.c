#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <ctype.h>
#define BUFSIZE 1024
#define PORT 4444
typedef struct filearg
{
    int file_size;
    int num_chars;
    int num_lines;
    int num_words;
} filearg;
void count_file_stats(const char *filename, filearg *buf)
{
    buf->file_size = 0;
    buf->num_chars = 0;
    buf->num_lines = 0;
    buf->num_words = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int ch;
    int in_word = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        (buf->file_size)++;
        (buf->num_chars)++;
        if (ch == "\n")
        {
            (buf->num_lines)++;
        }
        if (isspace(ch))
        {
            in_word = 0;
        }
        else if (in_word == 0)
        {
            in_word = 1;
            (buf->num_words)++;
        }
    }
    if (buf->file_size > 0 && ch == EOF && !isspace(ch))
    {
        (buf->num_lines)++;
    }
    fclose(file);
}
int main(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    int resBild = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    if (resBild < 0)
    {
        perror("bind\n");
        exit(1);
    }
    int resListen = listen(sockfd, 3);
    if (resListen < 0)
    {
        perror("Listen\n");
        exit(1);
    }
    socklen_t len = sizeof(client);
    int clientfd = accept(sockfd, (struct sockaddr *)&client, &len);
    printf("Connected to\n");
    if (clientfd < 0)
    {
        perror("Accept\n");
        exit(1);
    }
    char buf[] = "Connection ";
    send(clientfd, buf, sizeof(buf), 0);
    recv(clientfd, buf, sizeof(buf), 0);
    filearg file;
    count_file_stats(buf, &file);
    send(clientfd, &file, sizeof(buf), 0);
    close(clientfd);
    close(sockfd);
    printf("Size:%d\n", file.file_size);
    printf("Number of characters:%d\n", file.num_chars);
    printf("Number of Lines:%d\n", file.num_lines);
    printf("Number of words:%d\n", file.num_words);
    return 0;
}