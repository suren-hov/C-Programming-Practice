#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#define THREAD_POOL_SIZE 4

typedef struct {
    int *arr;
    int l;
    int r;
} Task;

extern Task task_queue[256];
extern int queue_size;

extern pthread_mutex_t queue_mutex;
extern pthread_cond_t queue_cond;
extern pthread_t thread_pool[THREAD_POOL_SIZE];

void init_thread_pool();
void *thread_pool_worker(void *arg);

#endif // THREAD_POOL_H
