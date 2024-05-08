#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define textSize 25
#define DEF_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH

int main()
{
    int fd = open("file-for-copy.txt", O_RDONLY);   
    if (fd == -1) exit(EXIT_FAILURE);    
    char buf[textSize];
    
    if (read(fd, buf, textSize) != textSize) exit(EXIT_FAILURE);
    printf("%s\n", buf);

    int new_file_fd = open("copied-file.txt", O_WRONLY | O_CREAT | O_EXCL, DEF_MODE);
    if (new_file_fd == -1) exit(EXIT_FAILURE);
    
    if(write(new_file_fd, buf, textSize) != textSize) exit(EXIT_FAILURE);

    if (close(fd) == -1) exit(EXIT_FAILURE);
    if (close(new_file_fd) == -1) exit(EXIT_FAILURE);
}

