#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <errno.h>
#include <time.h>

#define ARR_SIZE 10

/* Try to divide array and sum it by diving it into 2, 1 half for each process */
int main() {
    srand(time(NULL));

    int fd[2];
    int start, end;
    int arr[ARR_SIZE];

    for(int i=0; i<ARR_SIZE; i++) {
        arr[i] = rand() % 10;
        if(i == 0) {
            printf("Array generated:\n[%d, ", arr[i]);
        } else if(i == ARR_SIZE - 1) {
            printf("%d]\n", arr[i]);
        } else {
            printf("%d, ", arr[i]);
        }
    }

    if(pipe(fd) == -1) {
        return 1;
    }

    pid_t pid = fork();

    if(pid == 0) {
        start = 0;
        end = ARR_SIZE / 2;
    } else {
        start = ARR_SIZE / 2;
        end = ARR_SIZE;
    }

    int sum = 0;
    for(int i=start; i<end; i++) {
        sum += arr[i];
    }
    printf("Calculated partial sum: %d\n", sum);

    if(pid == 0) {
        close(fd[0]);

        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
    } else {
        close(fd[1]);

        int sum_child;
        read(fd[0], &sum_child, sizeof(sum_child));
        close(fd[0]);

        int total_sum = sum + sum_child;
        printf("Total sum: %d\n", total_sum);
        wait(NULL);
    }
    return 0;
}