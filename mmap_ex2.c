#define _GNU_SOURCE /* necessary for MAP_ANONYMOUS */
#include <stdio.h> /* printf type stuff */
#include <stdlib.h> /* for NULL */
#include <sys/mman.h> /* for mmap */
int main() {
    int n = 10;
    size_t size = n * sizeof(int);
    int *array = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    for(int i=0; i<n; i++) {
        array[i] = i*2;
        printf("array[%d] = %d\n", i, array[i]);
    }
    printf("Size of array: %ld\n", size);
    munmap(array, size);
    return 0;
}