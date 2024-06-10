#ifndef TPOOL_H
#define TPOOL_H

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

#define THREAD_COUNT 6

struct tpool {
	pthread_mutex_t lock;
	pthread_cond_t signal;
	pthread_t threads[THREAD_COUNT];
	queue_t queue;
	atomic_int queue_size;
	atomic_int shutdown;
};

void init_tpool(struct tpool *);
void submit_task(struct tpool *, task_t);
void *thread_main(void *);

#endif /* TPOOL_H */ 
