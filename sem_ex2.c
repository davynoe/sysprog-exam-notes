#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#define THREAD_NUM 16
#define LOGIN_MAX 4
sem_t s1;

void *routine(void *id) {
    printf("(%d)Waiting in the login queue\n", (int)(long)id);
    sem_wait(&s1); 
    printf("(%d) Logged in\n", (int)(long)id);
    sleep(rand() % 5 + 1);
    printf("(%d) Logged out\n", (int)(long)id);
    sem_post(&s1);
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t tid[THREAD_NUM];
    sem_init(&s1, 0, LOGIN_MAX); /* semaphore addr, pshared (shared between multiple processes), starting value */
    for(int i=0; i<THREAD_NUM; i++) {
        pthread_create(&tid[i], NULL, routine, (void *)(long)i);
    }
    for(int i=0; i<THREAD_NUM; i++) {
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&s1);
    return 0;
}