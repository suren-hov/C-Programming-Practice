#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void message_handler(int sig)
{
    static char current = 0;
    static int count    = 0;

    if (sig == SIGUSR2){
        current |= (1 << (7 - count));
    }

    ++count;

    if (count == 8) {
        write(1, &current, 1);
        current = 0;
        count = 0;
    }
}

int main()
{
    printf("server's pid: %d\n", getpid());

    signal(SIGUSR1, message_handler);
    signal(SIGUSR2, message_handler);

    while (1);
}