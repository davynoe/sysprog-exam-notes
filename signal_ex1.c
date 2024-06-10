#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if(pid == 0) {
        while(1) {
            printf("I wont die!\n");
            usleep(50000);
        }
    } else {
        sleep(1);
        /* kill doesnt mean killing */
        /* in UNIX, kill sends a signal */
        kill(pid, SIGKILL); /* pid will point to child in this case */
        printf("He died lol\n");
        wait(NULL);
    }

    return 0;
}