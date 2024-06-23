#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if (pid == 0)
    {
        char buf[15]; 
        int i = read(fd[0], buf, 15);
        buf[i] = '\0';
        printf("%s\n", buf);
        return 0;
    }
    else
    {
        write(fd[1], "hello world\n", 12);
    }
}
