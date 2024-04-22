#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t forkv;
    forkv = fork();
    if (forkv > 0)
        printf ("Hello from Parent with pid=%d!\n", getpid());
    else if (!forkv)
        printf ("Hello from Child with pid=%d!\n", getpid());
    else if (forkv == -1)
        perror ("fork");

}
