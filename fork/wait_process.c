#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t forkv = fork();
    if (forkv > 0) {
        wait(NULL);
        pid_t forkv2 = fork();
        if (forkv2 > 0) {
            wait(NULL);
            pid_t forkv3 = fork();
            if (forkv3 > 0) {
                wait(NULL);
            } else if (forkv3 == 0) {
                execl("/bin/ls", "ls", NULL);
            }
        } else if (forkv2 == 0) {
            execl("/bin/whoami", "whoami", NULL);
        }
    } else if (forkv == 0) {
        execl("/bin/date", "date", NULL);
    }
}
