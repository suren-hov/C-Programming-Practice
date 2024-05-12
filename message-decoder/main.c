#include <unistd.h>
#include <fcntl.h>

#define SIZE 4096

char decode(char sym)
{
    if (sym >= 'A' && sym <= 'Z'){
        if (sym <= 'C' && sym >= 'A')
            sym = 'Z' - (2 - (sym - 'A'));
        else 
            sym -= 3;
    } else if (sym >= 'a' && sym <= 'z'){
        if (sym <= 'c' && sym >= 'a'){
            sym = 'z' - (2 - (sym - 'a'));
        }
        else {
            sym -= 3;
        }
    }
    return sym;
}

int main()
{
    char buf[SIZE];
    int fd = open("_EncodedMessage.txt", O_RDONLY);
    int new_fd = open("output.txt", O_WRONLY);
    int size = read(fd, &buf, SIZE);

    for (int i = 0; i < SIZE; i++){
        buf[i] = decode(buf[i]);
    }

    write(new_fd, buf, size);
    return 0;
}