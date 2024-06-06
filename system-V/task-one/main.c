#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>

#define BUF_SIZE 1024
#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

struct shmseg {
    int buf[BUF_SIZE];
};

pthread_t tid[2]; 
pthread_mutex_t lock;

void* threadFunc(void* arg) 
{ 
    struct shmseg *shmp = (struct shmseg *) arg;
    pthread_mutex_lock(&lock); 
  
    srand(time(NULL));   // Initialization, should only be called once.

    for (int i = 0; i < 10; i++){
        shmp->buf[i] = rand() % 100; 
    }

    pthread_mutex_unlock(&lock); 
  
    return NULL; 
} 
  
void* threadFunc2(void* arg) 
{ 
    struct shmseg *shmp = (struct shmseg *) arg;
    pthread_mutex_lock(&lock); 
  
    for (int i = 0; i < 10; i++){
        printf("%d\n", shmp->buf[i]);
    }
    pthread_mutex_unlock(&lock); 
  
    return NULL; 
} 


int main()
{
    struct shmseg *shmp;
    int i, error;
    int key = ftok("./Dekstop", 1);

    int shmid = shmget(key, sizeof(struct shmseg), IPC_CREAT | OBJ_PERMS);
    if (shmid == -1) perror("shmget");
    
    shmp = shmat(shmid, NULL, 0);
    if (shmp == (void *) -1) perror("shmat");

    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 

    if (pthread_create(&(tid[0]),NULL, threadFunc, &shmp) != 0) perror("pthread_create");
    if (pthread_create(&(tid[1]),NULL, threadFunc2, &shmp) != 0) perror("pthread_create");

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);

    if (shmdt(&shmp) == -1) perror("shmdt");
    if (shmctl(shmid, IPC_RMID, 0) == -1) perror("shmctl");
    exit(EXIT_SUCCESS);
}