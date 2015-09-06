#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void writer(int *fd, char *argv[]);
void reader(int *fd, char *argv[]);

int main(int argc, char *argv[]) {
	int fd[2];

	pipe(fd);
	if(!fork())
		reader(fd, argv);  // child
	else
		writer(fd, argv);  // parent

	return 0;
}

void writer(int *fd, char *argv[]) {
	// close read side
	close(fd[0]);

	// all stdout operation will be directed to fd[0];
	dup2(fd[1], 1);

	// after referring it. Now close it. From now onwards output will
	// be written into fd[1] directly
	close(fd[1]);

	// execute a command
	execlp(argv[1], argv[1], NULL);
}
void reader(int *fd, char *argv[]) {
	// close write side
	close(fd[1]);

	// all stdin operation will be directed from fd[0];
	dup2(fd[0], 0);

	// After referring it. Now close it. From now onwards input will
	// be taken from fd[0] directly
	close(fd[0]);

	// execute a command
	execlp(argv[2], argv[2], NULL);
}
