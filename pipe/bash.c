#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#define CMDS 2
int main( void )
{
    char *cmds[3][15] = {
        {"/bin/ls", 0, 0},
        {"/usr/bin/grep", "send", 0},
       // {"/bin/cat", "cat", NULL}
    };
    int fds[2]; // [0] -> 3 ; [1] -> 4
    pipe(fds);

    for(int i = 0; i < CMDS; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            if (i == 0)
            {
                //ls
                dup2(fds[1], STDOUT_FILENO);
                close(fds[1]);
                close(fds[0]);
                execve(cmds[i][0], cmds[i], NULL);
            }
            else if(i == 1)
            {
                //grep
                dup2(fds[0], STDIN_FILENO);
                close(fds[0]);
                close(fds[1]);
                execve(cmds[i][0], cmds[i], NULL);
            }        
        }
        else
        {
            //parent
            for(int i = 0; i < CMDS; i++)
                wait(NULL);
            close(fds[1]);
        }
    }
}
