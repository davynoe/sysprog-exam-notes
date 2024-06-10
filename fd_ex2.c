    #include <sys/types.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
        /* open for read+write, create if doesnt exist, delete content if exists */
        int fd = open("file2.txt", O_RDWR | O_CREAT | O_TRUNC, 0666); 
        /* 0NNN is required if O_CREAT exists. N = file permissions: r=4, w=2, x=1 -> rw=6 */

        char *str = "Lorem ipsum dolor";

        size_t size = strlen(str) * sizeof(char);
        write(fd, str, size);

        char* buf = malloc(size);

        /* move mouse pointer back to beginning and read */
        lseek(fd, 0, SEEK_SET);
        read(fd, buf, size);

        printf("%s\n", buf);

        free(buf);
        close(fd);
        return 0;
    }
