#include <pthread.h>
#include "merge_sort.h"
#include "thread_pool.h"

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int left[n1], right[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void parallel_merge_sort(int arr[], int l, int r) {
    Task initial_task = {arr, l, r};

    pthread_mutex_lock(&queue_mutex);
    task_queue[queue_size++] = initial_task;
    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);

    // Wait for all tasks to complete
    pthread_mutex_lock(&queue_mutex);
    while (queue_size > 0) {
        pthread_cond_wait(&queue_cond, &queue_mutex);
    }
    pthread_mutex_unlock(&queue_mutex);
}
