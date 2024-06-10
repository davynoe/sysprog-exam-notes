#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd[2]; /* fd[0] - read, fd[1] - write | endpoints */
    if(pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }
    pid_t pid = fork();
    if (pid == 0) {
        close(fd[0]);

        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    } else {
        close(fd[1]);

        int y;

        read(fd[0], &y, sizeof(int));
        close(fd[0]);

        printf("Got from child: %d\n", y);
    }

    return 0;
}