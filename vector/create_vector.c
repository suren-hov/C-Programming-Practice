#include "vector.h"

struct Vector create_vector()
{
    struct Vector vector;
    vector.capacity = 8;
    vector.array = (int*) malloc(sizeof(int) * vector.capacity);
    vector.size = 0;

    return vector;
}