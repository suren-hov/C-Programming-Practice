#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void send_letter(char c, int pid)
{
    for (int i = 7; i >= 0; --i)
    {
        if (c & (1 << i)) {
            kill(pid, SIGUSR2);
        } else {
            kill(pid, SIGUSR1);
        }

        usleep(1000);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: a.out <message> <server pid>");
        exit(0);
    }

    char *message = argv[1];
    int server_pid = atoi(argv[2]);

    int i = 0;
    while (message[i] != 0) {
        send_letter(message[i++], server_pid);
    }
}