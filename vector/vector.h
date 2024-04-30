#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

struct Vector
{
    int *array;
    int size;
    int capacity;
};

struct Vector create_vector(); // default initialization, set capacity to some base number and allocate
void push_back(struct Vector *vector, int val); // push the value in the end
void insert(struct Vector *vector, int index, int val); // insert at the given index
void erase(struct Vector *vector, int index); // erase the element at index
void delete_vector(struct Vector *vector); // free the memory and set zero

#endif // !VECTOR_H
