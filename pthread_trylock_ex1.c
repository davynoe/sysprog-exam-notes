#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *thread_function(void *arg) {
    int thread_id = *((int *) arg);
    printf("Thread %d started\n", thread_id);

    // Attempt to lock the mutex without blocking
    int result = pthread_mutex_trylock(&mutex);

    if (result == 0) {
        // Mutex successfully locked
        printf("Thread %d locked the mutex\n", thread_id);

        // Accessing the shared resource (counter)
        counter++;
        printf("Thread %d incremented counter to %d\n", thread_id, counter);

        // Unlock the mutex after accessing the shared resource
        pthread_mutex_unlock(&mutex);
        printf("Thread %d unlocked the mutex\n", thread_id);
    } else if (result == EBUSY) {
        // Mutex is already locked by another thread
        printf("Thread %d failed to lock the mutex (it's already locked)\n", thread_id);
    } else {
        // An error occurred
        perror("pthread_mutex_trylock");
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
}

int main() {
    #define NUM_THREADS 10
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;

    // Create multiple threads
    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, (void *) &thread_args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);
    return 0;
}
