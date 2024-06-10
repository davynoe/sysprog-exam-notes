#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

char answer[100];


void give_hint() {
    if(strcmp(answer, "Ankara") != 0) {
        printf("It was Istanbul but it's changed by the way!\n");
    } else {
        printf("No hint needed damn\n");
    }
}

int main() {
    pid_t pid = fork();

    /* Child */
    if(pid == 0) {
        sleep(5);
        kill(getppid(), SIGUSR1);
        /* SIGUSR1 & SIGUSR2 user defined signals, communication signals */
    }
    /* Parent */ 
    else {
        struct sigaction sa;
        sa.sa_flags = SA_RESTART; /* cuz its on scanf */
        sa.sa_handler = give_hint;
        sigaction(SIGUSR1, &sa, NULL);

        printf("What is the capital of Turkey? :\n");
        scanf("%s", answer);
        if(strcmp(answer, "Ankara") == 0) {
            printf("Correct!\n");
        } else {
            printf("Wrong!\n");
        }
        wait(NULL);
    }
}