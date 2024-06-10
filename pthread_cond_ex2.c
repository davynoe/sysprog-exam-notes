#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
/* pthread_cond_wait, pthread_cond_broadcast, pthread_cond_signal */
int fuel = 0;
pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
void *fuel_filling(void *arg) {
    for(int i=0; i<5; i++) {
        pthread_mutex_lock(&mutexFuel);
        fuel += 10;
        printf("Filling fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_broadcast(&condFuel); /* tell all condFuel waiters to continue execution */
        sleep(1);
    }
}

void *car(void *arg) {
    pthread_mutex_lock(&mutexFuel);
    while(fuel < 40) { /* condition NEEDS to be in a while loop, signal can be misleading! */
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        /* equivalent to */
        /* pthread mutex unlock */
        /* wait for condfuel signal */
    }
    fuel -= 40;
    printf("Got fuel. left fuel... %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

int main() {
    int n_cars = 6, n_workers = 6;
    pthread_t cars[n_cars], workers[n_workers];

    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);

    for(int i=0; i<n_cars; i++) {
        pthread_create(&cars[i], NULL, car, NULL);
    }
    for(int i=0; i<n_workers; i++) {
        pthread_create(&workers[i], NULL, fuel_filling, NULL);
    }
    for(int i=0; i<n_cars; i++) {
        pthread_join(cars[i], NULL);
    }
    for(int i=0; i<n_workers; i++) {
        pthread_join(workers[i], NULL);
    }

    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}