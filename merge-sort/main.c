#include <stdio.h>
#include <pthread.h>
#include "merge_sort.h"
#include "thread_pool.h"

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    init_thread_pool();

    parallel_merge_sort(arr, 0, arr_size - 1);

    printf("Sorted array is \n");
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // Cleanup: Join all threads (not necessary here since we're running indefinitely)
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_cancel(thread_pool[i]);
        pthread_join(thread_pool[i], NULL);
    }

    return 0;
}
