#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main() {
	DIR *dp;
	struct dirent *dirp;

	dp = opendir("./");

	while((dirp = readdir(dp)) != NULL) {
		printf(" %20s ", dirp->d_name);
	}
	closedir(dp);
	return 0;
}