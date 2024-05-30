#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 20

typedef struct {
    int* array;
    int size;
} thread_args;

void* primeNumbers(int *array, int *size)
{
    int count = 0;
    for (int i = 3; i < *size; i++) {
        for (int j = 2; j * j < i; j++)
        {
            if (i % j == 0){
                array[count] = i;
                count++;
            }
        }
    }
    *size = count;
    return NULL;
}

void printArr(int *arr, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d\n", arr[i]);
    }
}

void* threadOneFunc(void* arg)
{
    primeNumbers(((thread_args*) arg)->array, &((thread_args*) arg)->size);
    return NULL;
}


void* threadTwoFunc(void* arg)
{
    printArr(((thread_args*) arg)->array, ((thread_args*) arg)->size);
    return NULL;
}

int main()
{
    pthread_t thread_one;
    pthread_t thread_two;
    thread_args args;

    int *arr = (int*) malloc(SIZE * sizeof(int));
    args.array = arr;
    args.size = SIZE;
    
    pthread_create(&thread_one, NULL, threadOneFunc, (void *) &args);
    pthread_join(thread_one, NULL);
    pthread_create(&thread_two, NULL, threadTwoFunc, (void *) &args);
    pthread_join(thread_two, NULL);

}