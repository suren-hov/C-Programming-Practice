#include <stdio.h>
#include "thread_pool.h"
#include "merge_sort.h"

Task task_queue[256];
int queue_size = 0;

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;
pthread_t thread_pool[THREAD_POOL_SIZE];

void *thread_pool_worker(void *arg) {
    while (1) {
        Task task;
        
        pthread_mutex_lock(&queue_mutex);
        while (queue_size == 0) {
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }

        task = task_queue[--queue_size];
        pthread_mutex_unlock(&queue_mutex);

        int l = task.l;
        int r = task.r;
        int *arr = task.arr;

        if (l < r) {
            int m = l + (r - l) / 2;

            Task left_task = {arr, l, m};
            Task right_task = {arr, m + 1, r};

            pthread_mutex_lock(&queue_mutex);
            task_queue[queue_size++] = left_task;
            task_queue[queue_size++] = right_task;
            pthread_cond_signal(&queue_cond);
            pthread_mutex_unlock(&queue_mutex);

            merge(arr, l, m, r);
        }
    }
    return NULL;
}

void init_thread_pool() {
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, thread_pool_worker, NULL);
    }
}
