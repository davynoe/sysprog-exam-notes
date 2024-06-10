/* 
   Consumer producer problem
   Shared buffer with multiple threads
   Producers create data in buffer
   Consumers take data in buffer

   Problems to solve:
   1) Manage shared memory access [prevent race condition]
   2) Checking if buffer is full (producers > consumers)
   3) Checking if buffer is empty (producers > consumers)


   Producers will create random numbers
   Consumers will take random numbers and print it on the screen
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define N_PRODUCERS 6
#define N_CONSUMERS 10
#define SLEEP_NS 100000
#define BUF_SIZE 10

sem_t semEmpty;
sem_t semFull;
pthread_mutex_t mutexBuffer;
int buffer[BUF_SIZE];
int count = 0;

void *producer(void *arg) {
    while(1) {
        /* Produce */
        int product = rand() % 100 + 1;

        /* Add to buffer */
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        usleep(SLEEP_NS);
        buffer[count] = product;
        count++;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
    return NULL;
}
void *consumer(void *arg) {
    while(1) {
        int product;

        /*  Get from buffer */
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        usleep(SLEEP_NS);
        product = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);

        /* Consume */
        printf("Got %d\n", product);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t threads[N_PRODUCERS + N_CONSUMERS];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, BUF_SIZE);
    sem_init(&semFull, 0, 0);

    for(int i=0; i<N_PRODUCERS+N_CONSUMERS; i++) {
        if(i < N_PRODUCERS) {
            if(pthread_create(&threads[i], NULL, producer, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if(pthread_create(&threads[i], NULL, consumer, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }
    for(int i=0; i<N_PRODUCERS + N_CONSUMERS; i++) {
        if(pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    pthread_mutex_destroy(&mutexBuffer);
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);

    return 0;
}