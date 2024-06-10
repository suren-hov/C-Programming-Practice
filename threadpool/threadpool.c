#include "threadpool.h"

typedef struct {
	struct tpool *tpool;
	int id;
} arg_t;

void init_tpool(struct tpool *tpool)
{
	pthread_mutex_init(&tpool->lock, NULL);
	pthread_cond_init(&tpool->signal, NULL);
	init_queue(&tpool->queue);
	tpool->queue_size = 0;
	tpool->shutdown = 0;
		
	printf("dbg thread init\n");
	for (int i = 0; i < THREAD_COUNT; ++i) {
		arg_t *arg = malloc(sizeof(arg));
		arg->tpool = tpool;
		arg->id = i;
		pthread_create(&tpool->threads[i], NULL, thread_main, arg);
		pthread_detach(tpool->threads[i]);
	}
}

void *thread_main(void *arg)
{
	arg_t *a = (arg_t *)arg;
	struct tpool *tpool = a->tpool;
	printf("dbg thread main\n");
	for (;;) {
		pthread_mutex_lock(&tpool->lock);
		while (tpool->queue_size == 0 && tpool->shutdown == 0) {
			pthread_cond_wait(&tpool->signal, &tpool->lock);
		}

		task_t task = seek(&tpool->queue);
		--tpool->queue_size;

		pthread_mutex_unlock(&tpool->lock);
		
		if (task.current_job == NULL)
			continue;	

		task.current_job(a->id);
	}
}

void submit_task(struct tpool *tpool, task_t task)
{
	push_back(&tpool->queue, task);
	++tpool->queue_size;
	pthread_cond_broadcast(&tpool->signal);
}
