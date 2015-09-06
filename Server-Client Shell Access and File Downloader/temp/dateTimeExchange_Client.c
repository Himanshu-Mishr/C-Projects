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

#define IPADDR "127.0.0.1"
#define PORTNUMBER 5052


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
	servAdd.sin_addr.s_addr = inet_addr(IPADDR);

	sleep(2);

	// connect
	if(connect(server, (struct sockaddr *) &servAdd, sizeof(servAdd))  < 0) {
		fprintf(stderr, "connect() failed, exiting\n");
		exit(3);
	}
	// receive information from server
	char in_buf[100];
	recv(server, in_buf, sizeof(in_buf), 0);
    printf("\nServer > %s", in_buf);
    close(server);
}