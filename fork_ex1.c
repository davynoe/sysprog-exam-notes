#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
int main() {
    pid_t pid = fork();
    int n;
    if(pid == 0)  n = 1;
    else {
        n = 6;
        wait(NULL);
    }
    for(int i = n; i <n+5; i++) {
        printf("%d ", i);
        fflush(stdout);
    }
    printf("\n");
    return 0;
}