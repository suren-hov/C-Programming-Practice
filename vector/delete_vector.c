#include "vector.h"

void delete_vector(struct Vector *vector)
{
    free(vector->array);
    vector->array = NULL;
    vector->size = 0;
    vector->capacity = 0;
}