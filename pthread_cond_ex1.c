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
        fuel += 15;
        printf("Filling fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel); /* only signals 1 thread that waits */
        /*suitable for this program, since only 1 thread waiting */
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
    pthread_t tid1, tid2;
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    pthread_create(&tid1, NULL, car, NULL);
    pthread_create(&tid2, NULL, fuel_filling, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL); 

    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}