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

void child(int sd) {
	char message[255];

	while(1) {
		// fprintf(stderr, "Enter line to send to client\n");
		// fgets(message, 254, stdin);
		// write(sd, message, strlen(message)+1);

		if(!read(sd, message, 255)) {
			close(sd);
			fprintf(stderr, "Bye client dead, wait for a new client\n");
		exit(0);
		}
		fprintf(stderr, "Client send back: %s\n", message);
	}
}

int main(int argc, char const *argv[]) {
	int sd, client;
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

	while(1) {  /* reach here for every new connection */

		unsigned int clientSockAddr_len = sizeof(clientAdd);

		// accept
		client = accept(sd, (struct sockaddr *) &clientAdd, &clientSockAddr_len);
		printf("Got a client\n");
		if(!fork())  /* allow only child process to pass and kill parent. And after that parent is ready for new connection*/
			child(client);
		close(client);
	}
	return 0;
}