#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void child(int *);
void parent(int *);

int main() {
	int fd[2]; /* defining file descriptor array */

	// make pipe of them
	if(pipe(fd) == -1){
		exit(1);
	}
	// forking this process
	if(fork() == 0)
		child(fd);
	else
		parent(fd);
	return 0;
}

void parent(int *fd) {
	char ch;

	close(fd[1]);  /* closing write side when reading */
	printf("Child has sent the message : \n");
	do
	{
		read(fd[0], &ch, 1);
		printf("%c", ch);
		if(ch == '\n')
			break;
	} while (1);
}

void child(int *fd) {
	char message[255] = "Hello here is my data ..\n";

	close(fd[0]);  /* closing read side when writing */

	write(fd[1], message, 26);
}



