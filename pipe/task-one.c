#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main()
{
    int pipfd[2];
    int child;

    char message[] = "Hello from parent";
    char buffer[BUFFER_SIZE];

    int result = pipe(pipfd);
    if (result == -1) {
        perror("Invalid pipes");
    }

    child = fork();
    if (child < 0) {
        perror("Invalid fork");
        return 1;
    } else if (child == 0) {
        int RBytes = read(pipfd[0], buffer, BUFFER_SIZE);
        if (RBytes == -1) {
            perror("Invalid read");
        }
        printf("Message from parent: %s", buffer);
        close(pipfd[0]);
    } else {
        int WBytes = write(pipfd[1], message, strlen(message));
        if (WBytes < 0) {
            perror("Invalid write");
        }
        close(pipfd[0]);
        wait(NULL);
    }
}