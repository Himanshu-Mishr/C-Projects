// coder   : Himanshu Mishra
// Program : TCP Server

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
// contains Internet socket address structure Required for connection b/w different computer
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

#define PORTNUMBER 5020
#define IP_ADDRS "127.0.0.1"

int main(int argc, char *argv[]) {
	char message[100];
	int server;
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

	sleep(2);

	// connect
	if(connect(server, (struct sockaddr *) &servAdd, sizeof(servAdd))  < 0) {
		fprintf(stderr, "connect() failed, exiting\n");
		exit(3);
	}

	while(1) {  /* infinite loop for chat */
		// read message from client
		// if (read(server, message, 255) < 0) {
		// 	fprintf(stderr, "read() error \n");
		// 	exit(3);
		// }
		// fprintf(stderr, "Server's message: %s\n", message);

		fprintf(stderr, "Enter the $ sign to quit or a message for the server\n");
		fgets(message, 254, stdin);
		if(message[0] == '$') {
			close(server);
			exit(0);
		}
		// write the message
		write(server, message, strlen(message)+1);
	}
}