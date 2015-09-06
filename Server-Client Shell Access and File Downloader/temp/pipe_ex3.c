#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void child(int *fd, char *argv[]);
void parent(int *fd, char *argv[]);

int main(int argc, char *argv[]) {
	int fd[2]; /* creating array of file descriptor*/

	/* creating a pipe on fd */
	if (pipe(fd) == -1) exit(1);

	if(fork() > 0)
		parent(fd, argv);
	else
		child(fd, argv);
	return 0;
}

void parent(int *fd, char *argv[]) {
	close(fd[0]);     /* close read  */
	dup2(fd[1], 1);   /* 1 is stdout */
	close(fd[1]);     /* close write */
	execlp(argv[1], argv[1], NULL);
}

void child(int *fd, char *argv[]) {
	close(fd[1]);     /* close write */
	dup2(fd[0], 0);   /* 0 is stdin */
	close(fd[0]);     /* close read/stdin*/
	execlp(argv[1], argv[1], NULL);
}