#include <stdio.h>
#include <sys/signal.h>

void action() {sleep(1);}
void child(FILE *);
void parent(FILE *, pid_t);

int main(int argc, char const *argv[]) {
	FILE *fp;
	pid_t pid;
	int childRes;

	/* opening a file*/
	fp = fopen("/tmp/ipoc.txt", "w+");
	/* turning off buffering */
	setbuf(fp, NULL);

	if((pid=fork()) == 0)
		child(fp);
	parent(fp, pid);

	/*
	child first goes to child()
		  then goes to parent()

	parent goes to parent()
	*/

	return 0;
}

void parent(FILE *fp, pid_t pid) {
	int childRes, n=0;

	while (1) {
		signal(SIGUSR1, action);
		pause();
		rewind(fp);
		fread(&childRes, sizeof(int), 1, fp);
		printf("\nParent child result : %d\n", childRes);
		if(++n > 5) {
			printf("Parent : work done, bye bye\n");
			kill(0, SIGTERM);
		}
		printf("\nParent : waiting for child\n");
		kill(pid, SIGUSR1);
	}
}
void child(FILE *fp) {
	int value;

	while (1) {
		sleep(1);
		value = random()%100;
		rewind(fp);
	}
}














