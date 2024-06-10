#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef void *(*job)(void *);

typedef struct {
	job current_job;
	void *arg;
} task_t;

struct node_t {
	task_t task;
	struct node_t *next;
};

typedef struct {
	struct node_t *head;
	pthread_mutex_t lock;
} queue_t;

void init_queue(queue_t *);
task_t seek(queue_t *);
void push_back(queue_t *, task_t);

#endif /* QUEUE_H */
