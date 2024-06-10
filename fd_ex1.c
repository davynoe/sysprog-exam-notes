#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    /* open for read only */
    int fd = open("file.txt", O_RDONLY);

    /* get properties of the file (ex. size)*/
    struct stat sb;
    fstat(fd, &sb);

    /* make a buffer of that size and read into it */
    char *buf = malloc(sb.st_size);
    read(fd, buf, sb.st_size);

    printf("%s\n", buf);

    /* free allocated memory & close opened file descriptor */
    free(buf);
    close(fd);

    return 0;
}
