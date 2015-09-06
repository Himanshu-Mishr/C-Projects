#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
void player(char *s, int *fd1, int *fd2);

int main(int argc, char *argv[]) {
	int fd1[2], fd2[2], fd3[2], fd4[2];
	char turn = 'T';

	printf("This is a two player game with a referee\n");
	pipe(fd1);
	pipe(fd2);
	if(!fork())
		player("TOTO", fd1, fd2);

	close(fd1[0]);  /* parent only write to pipe 1*/
	close(fd2[1]);  /* parent only read from pipe 2*/

	pipe(fd3);
	pipe(fd4);
	if(!fork())
		player("TITI", fd3, fd4);

	close(fd3[0]);  /* parent only write to pipe 3*/
	close(fd4[1]);  /* parent only read from pipe 4*/

	while(1) {
		printf("Referee : TOTO plays\n");
		write(fd1[1], &turn, 1);
		read(fd2[0], &turn, 1);

		printf("Referee : TITI plays\n");
		write(fd3[1], &turn, 1);
	}
}

void player(char *s, int *fd1, int *fd2) {
	int points = 0;
	int dice;
	long int ss=0;
	char turn;

	while(1) {
		read( fd1[0], &turn, 1);
		printf("%s: playing my dice.\n", s);
		dice = (int) time(&ss) %10 + 1;
		printf("%s: got %d points. \n", s, dice);
		points += dice;
		printf("%s :  Total so far %d\n", s, points);
		if(points > 50) {
			printf("%s: game over I won\n", s);
			kill(0, SIGTERM);
		}
		sleep(5);
		write(fd2[1], &turn, 1);
	}
}













