#include "exam.h"
int main() {
	size_t size = sysconf(_SC_PAGE_SIZE);
	sem_t *t = mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_init(t, 1, 0);
	int *hs = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	int pid = fork();
	if (pid == 0){
		sem_wait(t);
		hs[0] = 1;
		printf("child: %d\n", hs[0]);
	}
	else {
		hs[0] = 2;
		sem_post(t);
		wait(NULL); /*wait for child!!*/
		printf("parent: %d\n", hs[0]);
	}
	munmap(hs, size);
}