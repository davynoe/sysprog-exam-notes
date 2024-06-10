#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define THREAD_NUM 4

sem_t s1;

void *routine(void *id) {
    sem_wait(&s1); /* if s1>0 , s1-- and execute; if s1==0, wait */
    sleep(1);
    printf("Hello from thread %d\n", (int)(long)id);
    sem_post(&s1); /* s1++ */
    return NULL;
}

int main() {
    pthread_t tid[THREAD_NUM];
    sem_init(&s1, 0, 2); /* semaphore addr, pshared (shared between multiple processes), starting value */
    for(int i=0; i<THREAD_NUM; i++) {
        pthread_create(&tid[i], NULL, routine, (void *)(long)i);
    }
    for(int i=0; i<THREAD_NUM; i++) {
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&s1);
    return 0;
}