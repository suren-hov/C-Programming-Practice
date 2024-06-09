#include "queue.h"

#include <stdio.h>

int main()
{
	queue_t queue;
	init_queue(&queue);

	push_back(&queue, (task_t){NULL, NULL});
	push_back(&queue, (task_t){NULL, NULL});
	push_back(&queue, (task_t){NULL, NULL});

	task_t task = seek(&queue);

	printf("%p %p\n", task.current_job, task.arg);
}
