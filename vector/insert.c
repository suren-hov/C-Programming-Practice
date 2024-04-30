#include "vector.h"

void insert(struct Vector *vector, int index, int val)
{
    if(index < 0 || index >= vector->size){
        exit(0);
    }

    if(vector->capacity == vector->size){
        vector->capacity *= 2;
        vector->array = (int*) realloc(vector->array, vector->capacity);
    }

    for(int i = vector->size; i > index; --i){
        vector->array[i] = vector->array[i - 1];
    }

    vector->array[index] = val;
    vector->size += 1;
}