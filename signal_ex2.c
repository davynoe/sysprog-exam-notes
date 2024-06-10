#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

/* Fun Fact: SIGKILL CANNOT BE HANDLED (its sort of like an order) */

/* handle CTRL+Z (terminal stop) */
void handle_sigtstp() {
    /* PRINTF IS NOT SAFE TO USE IN SIG HANDLERS */
    write(1, "\nStop not allowed\n", strlen("\nStop not allowed\n")/sizeof(char));
}

/* handle CTRL+C (interrupt)*/
void handle_sigint() {
    write(1, "\nFine, you win...\n", strlen("\nFine, you win...\n")/sizeof(char));
    exit(0);
}

int main() {
    /* Using sigaction to handle CTRL+Z */
    struct sigaction sa; 
    sa.sa_handler = handle_sigtstp;
    sigaction(SIGTSTP, &sa, NULL);

    /* Using signal to handle CTRL+C (easier way) */
    signal(SIGINT, handle_sigint);

    while(1) {
        sleep(1);
        printf("Haha you're stuck!\n");
    }

    return 0;
}