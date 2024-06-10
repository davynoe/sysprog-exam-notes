#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

void *routine(void *tid) {
    int id = (int) (long) tid; // Explicitly cast to long, then int
    int result = id + (rand() % 6 + 1);
    return (void *) (long) result; // Explicitly cast to long, then void *
}

int main() {
    int n = 3;
    pthread_t tid[n];
    int results[n];

    srand(time(NULL));
    for(int i=0; i<n; i++) {
        pthread_create(&tid[i], NULL, routine, (void *) (long) i); // Explicitly cast to long, then void *
    }
    for(int i=0; i<n; i++) {
        void *res;
        pthread_join(tid[i], &res);
        results[i] = (int) (long) res; // Explicitly cast to long, then int
    }
    for(int i=0; i<n; i++) {
        printf("result %d: %d\n", i, results[i]);
    }
    return 0;
}