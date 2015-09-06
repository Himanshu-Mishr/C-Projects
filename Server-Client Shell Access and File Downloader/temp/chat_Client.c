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

int main(int argc, char *argv[]) {
	char message[255];
	int server, pid, n;
	socklen_t len;
	struct sockaddr_in servAdd;

	// socket
	if((server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Could not create socket\n");
		exit(1);
	}

	servAdd.sin_family = AF_INET;
	servAdd.sin_port = htons((uint16_t)PORTNUMBER);
	servAdd.sin_addr.s_addr = inet_addr(IP_ADDRS);

	// connect
	if(connect(server, (struct sockaddr *) &servAdd, sizeof(servAdd))  < 0) {
		fprintf(stderr, "connect() failed, exiting\n");
		exit(3);
	}

	// receive test message from server, to start chat.
	read(server, message, 255);
	fprintf(stderr, "message received: %s\n", message);

	pid=fork();

	if(pid) { /*parent*/
		while(1) {  /* reading server's messages */
			if( (n=read(server, message, 255)) ) {
				message[n] = '\0';
				fprintf(stderr, "%s\n", message);
				if(!strcasecmp(message, "Bye\n")) {
					kill(pid, SIGTERM);
					exit(0);
				}
			}
		}
	}
	else { /*child*/
		while(1) { /*reading message from stdin*/
			if( (n=read(0, message, 255)) ) {
				message[n] = '\0';
				write(server, message, strlen(message)+1);
				if(!strcasecmp(message, "Bye\n")) {
					kill(getppid(), SIGTERM);
					exit(0);
				}
			}
		}
	}
}
