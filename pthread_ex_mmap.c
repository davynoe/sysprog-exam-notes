#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/mman.h>

void *routine(void *id) {
    int result = rand() % 6 + 1;
    printf("Job of thread %d done\n", (int *)id);
    return (void *)result;
}

int main() {
    srand(time(NULL));
    #define THREAD_COUNT 6

    size_t size = THREAD_COUNT * sizeof(int);
    pthread_t *tid = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    for(int i=0; i<THREAD_COUNT; i++) {
        pthread_create(&tid[i], NULL, routine, (void *)i);
    }

    size_t resultSize = THREAD_COUNT * sizeof(void *);
    void **results = mmap(NULL, resultSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    for(int i=0; i<THREAD_COUNT; i++) {
        pthread_join(tid[i], &results[i]);
    }

    for(int i=0; i<THREAD_COUNT; i++) {
        printf("Result of thread %d : %d\n", i, (int *)results[i]);
    }

    return 0;
}