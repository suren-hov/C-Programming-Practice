#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main( void )
{
    int rd_fifo = open("./pip", O_RDONLY);
    char buf[1024];
    int r = read(rd_fifo, buf, 1024);
    buf[r] = '\0';
    printf("%s\n", buf);
    close(rd_fifo);
}