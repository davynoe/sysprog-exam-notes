#define _GNU_SOURCE /* necessary for MAP_ANONYMOUS */
#include <stdio.h> /* printf type stuff */
#include <stdlib.h> /* for NULL */
#include <sys/mman.h> /* for mmap */
#include <unistd.h> /* for sysconf (get unix/linux variables) */
#include <sys/wait.h> /* for wait */
int main() {
    size_t size = sysconf(_SC_PAGE_SIZE);
    int *hs = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int pid = fork();
    /* child */
    if (pid == 0) {
        hs[0] = 0;
        printf("for child: hs[0] = %d\n", hs[0]);
    }
    /* parent */
    else {
        hs[0] = pid;
        wait(NULL); /* wait for child */
        printf("for parent: hs[0] = %d\n", hs[0]);
    }
    return 0;
}