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
    int first_pipe_fd[2];
    int second_pipe_fd[2];

    int child;

    char message[] = "Hello from parent\n";
    char message_two[] = "Hello from child\n";

    char first_buffer[BUFFER_SIZE];
    char second_buffer[BUFFER_SIZE];

    int first_channel = pipe(first_pipe_fd);
    if (first_channel == -1) {
        perror("Invalid first pipes");
    }

    int second_channel = pipe(second_pipe_fd);
    if (second_channel == -1) {
        perror("Invalid second pipes");
    }

    child = fork();
    if (child < 0) {
        perror("Invalid fork");
        return 1;
    } else if (child == 0) {
        int RBytes = read(first_pipe_fd[0], first_buffer, BUFFER_SIZE);
        if (RBytes == -1) {
            perror("Invalid read");
        }
        printf("Message from parent: %s", first_buffer);

        int WBytes_two = write(second_pipe_fd[1], message_two, strlen(message_two));
        if (WBytes_two < 0) {
            perror("Invalid write");
        }
    } else {
        int WBytes = write(first_pipe_fd[1], message, strlen(message));
        if (WBytes < 0) {
            perror("Invalid write");
        }

        int RBytes_two = read(second_pipe_fd[0], second_buffer, BUFFER_SIZE);
        if (RBytes_two == -1) {
            perror("Invalid read");
        }
        printf("Message from child: %s", second_buffer);
        close(first_pipe_fd[0]);
        close(second_pipe_fd[1]);
        wait(NULL);
    }
}