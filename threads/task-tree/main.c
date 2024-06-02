#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static intmax_t glob = 374;

static void *threadFunc(void *arg){
    int status = pthread_mutex_lock(&mtx);
    if (!status) perror("mutex_lock");

    *((intmax_t*) arg) *= 1000000;

    status = pthread_mutex_unlock(&mtx);
    if (!status) perror("mutex_unlock");

    return NULL;
}
    
int main()
{
    pthread_t thread_one, thread_two;
    pthread_attr_t attr;

    int status = pthread_create(&thread_one, NULL, threadFunc, &glob);
    if (!status) perror("pthread_create");

    status = pthread_create(&thread_two, NULL, threadFunc, &glob);
    if (!status) perror("pthread_create");

    status = pthread_join(thread_one, NULL);
    if (!status) perror("pthread_join");

    status = pthread_join(thread_two, NULL);
    if (!status) perror("pthread_join");

    printf("glob = %ld\n", glob);
}