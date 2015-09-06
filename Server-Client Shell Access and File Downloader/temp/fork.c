#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void myProcessID() {
	printf("My Process ID  : %d \n", getpid());
	printf("My Parent  ID  : %d \n", getppid());
}

int main() {
	pid_t pid;

	pid = fork();
	// error detection
	if (pid < 0) {
		perror("Error during fork() statment.");
		exit(1);
	}
	// detect parents
	if (pid > 0) {  /* Parent Code Area*/
		printf("This is parent part of code.\n");
		myProcessID();
	}
	else if (pid == 0) {  /*Child Code Area*/
		printf("This is child part of code.\n");
		myProcessID();
	}
	return 0;
}