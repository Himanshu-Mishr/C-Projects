#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	// printf("My process id is  : %d \n", getpid());
	// printf("My parent's process id is  : %d \n", getppid());
	pid_t pid = fork();

	if(pid < 0)  {
		perror("Error in executing fork().");
		return 1;
	}
	if(pid > 0)
		printf("This is Parent Process. Its id: %d and value of pid : %d\n", getpid(), pid);

	else if(pid == 0)
		printf("This is Child Process. Its id: %d and value of pid : %d\n", getpid(), pid);
	return 0;
}