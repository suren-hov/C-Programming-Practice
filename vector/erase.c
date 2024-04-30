#include "vector.h"

void erase(struct Vector *vector, int index)
{

    if(index < 0 || index >= vector->size) exit(0);

    for (int i = index; i < vector->size - 1; i++)
    {
        vector->array[i] = vector->array[i + 1]; 
    }
    vector->size -= 1;
}