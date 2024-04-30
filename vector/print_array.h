#ifndef PRINT_ARRAY
#define PRINT_ARRAY
#include <stdio.h>

#define PRINT_ARRAY_FUNCTION(x, len) \
    for(int x##_i = 0; x##_i < len; x##_i++){ \
        printf("%d:%d\n", x##_i, x[x##_i]); \
    }

int print_array(int *array, int length)
{
    PRINT_ARRAY_FUNCTION(array, length)
    return 0;
}
#endif // !PRINT_ARRAY