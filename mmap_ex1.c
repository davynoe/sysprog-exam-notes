#define _GNU_SOURCE /* necessary for MAP_ANONYMOUS */
#include <stdio.h> /* printf type stuff */
#include <stdlib.h> /* for NULL */
#include <fcntl.h> /* for open flags */
#include <sys/mman.h> /* for mmap */
#include <unistd.h> /* for sysconf */
int main() {
    int fd = open("file.txt", O_RDONLY);

    if(fd == -1) {
        perror("fd");
        close(fd);
        return 1;
    }

    size_t size = sysconf(_SC_PAGESIZE); /* usually 4 KBs */
    void *map = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

    printf("%s\n", (char *)map);
    
    close(fd);
    munmap(map, size);
    return 0;
}