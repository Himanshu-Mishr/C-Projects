#include <stdio.h>
#include <unistd.h>

int main()  {
	alarm(4);
	while(1) {
		printf("going to sleepZZZZzzzz");
		sleep(1);
	}
	return 0;
}