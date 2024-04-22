#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Forking the process
    pid_t pid = fork();
    
    if (pid < 0) {
        // Error handling for fork failure
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process executing /bin/ls...\n");
        // Replace the current process with /bin/ls
        if (execlp("/bin/ls", "ls", NULL) == -1) {
            // Error handling for execlp failure
            perror("execlp failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        // Wait for the child process to complete its execution
        int status;
        if (wait(&status) == -1) {
            // Error handling for wait failure
            perror("Wait failed");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process exited abnormally\n");
        }
    }
    
    return 0;
}

