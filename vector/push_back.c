#include "vector.h"

void push_back(struct Vector *vector, int val)
{
    if(vector->capacity == vector->size){
        vector->capacity *= 2;
        vector->array = (int*)realloc(vector->array, vector->capacity);
    }
    vector->array[vector->size] = val;
    vector->size += 1;
}