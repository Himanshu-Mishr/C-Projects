#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* Equivalent to "sort < file1 | uniq*/
#include<stdio.h>
int main()
{
	int fd[2];
	FILE *fp = fopen("file1.txt","r");

	FILE *wp = fopen("file2.txt","w");

	dup2(fileno(fp), fileno(stdin));
	dup2(fileno(wp), fileno(stdout));
	// fclose(fp);

	char line1[100];
	char line2[100];
	scanf("%s %s", line1, line2);
	printf("%s %s\n", line1, line2);
	// execl(line1,line2,(char*) 0);
	execlp(line1, line2, NULL);



	pipe(fd);

	if (fork() == 0)
	{
		dup2(fd[1],fileno(stdout));
		close(fd[0]);close(fd[1]);
		execl("/bin/ls","ls",(char*) 0);exit(2);
	}else{
		dup2(fd[0],fileno(stdin));
		close(fd[0]);close(fd[1]);
		execl("/usr/bin/ls","ls",(char*)0);exit(3);
	}
	return 0;
}