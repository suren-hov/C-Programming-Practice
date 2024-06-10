#include "threadpool.h"

#include <stdio.h>

void *f(void *arg)
{
	printf("hello from f %d\n", (int)arg);
	return NULL;
}


void *g(void *arg)
{
	printf("hello from g%d\n", (int)arg);
	return NULL;
}

int main(int argc, char *argv[])
{
	struct tpool tpool;
	init_tpool(&tpool);

	for (int i = 0; i < 10; ++i) {
		if (i % 2)
			submit_task(&tpool, (task_t){f, NULL});
		else 
			submit_task(&tpool, (task_t){g, NULL});
	}

	while (1);	
}
