#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main( void )
{
    int fifo = mkfifo("pip", 0666);
    int wr_fifo = open("./pip", O_WRONLY);
    char buf[1024];
    int r = read(0, buf, 1024);
    buf[r] = '\0';
    write(wr_fifo, buf, strlen(buf));
    close(wr_fifo);
}