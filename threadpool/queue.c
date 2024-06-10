#include "queue.h"

void init_queue(queue_t *queue)
{
	queue->head = NULL;
	pthread_mutex_init(&queue->lock, NULL);
}

task_t seek(queue_t *queue)
{
	pthread_mutex_lock(&queue->lock);
	task_t current_task = queue->head->task;
	struct node_t *next = queue->head->next;
	free(queue->head);
	queue->head = next;
	pthread_mutex_unlock(&queue->lock);
	return current_task;
}

void push_back(queue_t *queue, task_t new_task)
{
	struct node_t *new_node = (struct node_t *)malloc(sizeof(struct node_t));
	new_node->next = NULL;
	new_node->task = new_task;

	pthread_mutex_lock(&queue->lock);
	if (queue->head == NULL) {
		queue->head = new_node;
		pthread_mutex_unlock(&queue->lock);
		return;
	}
	
	struct node_t *tmp = queue->head;
	while (tmp->next != NULL) 
		tmp = tmp->next;

	tmp->next = new_node;
	pthread_mutex_unlock(&queue->lock);
}
