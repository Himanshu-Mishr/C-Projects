#include <stdio.h>
#include <pthread.h>
void *myThreadFunc(void *x) {
	for(int i = 0; i < 5; i++)
		printf("New thread is here.\n");
	return NULL;
}


int main(int argc, char const *argv[]) {
	pthread_t threadId;

	fork();
	// create a new thread to run myThreadFunc
	pthread_create(&threadId, NULL, myThreadFunc, NULL);
	sleep(2);
	for (int i = 0; i < 5; ++i) {
		printf("Original thread is here\n");
	}
	return 0;
}