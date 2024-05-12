#include <unistd.h>
#include <fcntl.h>

#define SIZE 4096
#define BIG_START_POINT 'A'
#define BIG_END_POINT 'Z'
#define SMALL_START_POINT 'a'
#define SMALL_END_POINT 'z'
#define BIG_C_SYMBOL 'C'
#define SMALL_C_SYMBOL 'c'
#define SHIFT_COUNT 3

char decode(char sym)
{
    if (sym >= BIG_START_POINT && sym <= BIG_END_POINT){
        sym = sym <= BIG_C_SYMBOL && sym >= BIG_START_POINT ?
            BIG_END_POINT - (SHIFT_COUNT - 1 - (sym - BIG_START_POINT)) : 
            sym - SHIFT_COUNT;
    } else if (sym >= SMALL_START_POINT && sym <= SMALL_END_POINT){
        sym = sym <= SMALL_C_SYMBOL && sym >= SMALL_START_POINT ?
            SMALL_END_POINT - (SHIFT_COUNT - 1 - (sym - SMALL_START_POINT)) :
            sym - SHIFT_COUNT;
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
    close(fd);
    close(new_fd);

    return 0;
}