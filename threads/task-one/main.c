#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LENGTH 5

int sumOfArray(int *array, int length)
{
    int sum = 0;
    for (size_t i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum;
}

typedef struct arr{
    int* arr;
    int size;
    int res;
}arr;

void *thread_func(void *ptr) {
    ( (arr*)ptr)->res = sumOfArray(((arr*)ptr)->arr, ((arr*)ptr)->size);
    return NULL;
}

int main()
{
    pthread_t pthread;

    arr arrays;
    int array[LENGTH] = {1, 2, 3, 4, 5};

    arrays.arr = array;
    arrays.size = LENGTH;

    int status = pthread_create(&pthread, NULL, thread_func, (void *)&arrays);
    pthread_join(pthread,NULL);
    printf("Result is: %d\n",arrays.res);


}