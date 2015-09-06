// coder   : Himanshu Mishra
// Program : TCP Server

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

#define PORTNUMBER 5020
#define IP_ADDRS "127.0.0.1"

void child(int sd) {
	char message[255];
	int n, pid;

	// write : starting message
	write(sd, "start chatting", 16);
	pid=fork();
	if(pid) {  /* Parent is allowed here */
		while(1) {
			/*read incoming msg from server*/
			if( (n=read(sd, message, 255)) ) {
				message[n] = '\0';
				/*print it on screen*/
				fprintf(stderr, "%s\n", message);
				if(!strcasecmp(message, "Bye\n")) {
					kill(pid, SIGTERM);
					exit(0);
				}
			}
		}
	}
	else { /*child*/
		while(1) {  /*read msg from client/stdin*/
			if( (n=read(0, message, 255)) ) {
				message[n] = '\0';
				/* send it to server*/
				write(sd, message, strlen(message)+1);
				if(!strcasecmp(message, "Bye\n")) {
					kill(getppid(), SIGTERM);
					exit(0);
				}
			}
		}
	}
}

int main(int argc, char const *argv[]) {
	int sd, client, status;
	socklen_t len;
	struct sockaddr_in servAdd;
	struct sockaddr_in clientAdd;

	// socket
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Could not create socket\n");
		exit(1);
	}

	servAdd.sin_family = AF_INET;
	servAdd.sin_addr.s_addr = inet_addr(IP_ADDRS);
	servAdd.sin_port = htons((uint16_t)PORTNUMBER);

	// bind
	bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));

	// listen
	listen(sd, 5);

	while(1) { /*reach here for every new connection*/
		unsigned int clientSockAddr_len = sizeof(clientAdd);

		// accept
		client = accept(sd, (struct sockaddr *) &clientAdd, &clientSockAddr_len);
		printf("Got a client\n");
		if(!fork())  /* allow only child process to pass and kill parent. And after that parent is ready for new connection */
			child(client);
		close(client);
		waitpid(0, &status, WNOHANG); /*wait for child(0) to exit*/
	}
	return 0;
}