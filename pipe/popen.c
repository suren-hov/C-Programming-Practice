#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main( void )
{
    FILE* fp = popen("ls", "w");
    char buf[1024];
    fgets(buf, 1024, fp);
    printf("%s", buf);
}