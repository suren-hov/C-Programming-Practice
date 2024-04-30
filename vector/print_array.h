#ifndef PRINT_ARRAY
#define PRINT_ARRAY

#include <stdio.h>

int print_array(int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d:%d\n", i, array[i]);
    }
}
#endif // !PRINT_ARRAY