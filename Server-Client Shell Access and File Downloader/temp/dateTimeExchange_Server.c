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
	char *myTime;
	time_t currentUnixTime;
	int sd, client;
	socklen_t len;
	struct sockaddr_in servAdd;

	// socket
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Could not create socket\n");
		exit(1);
	}
	servAdd.sin_family = AF_INET;
	servAdd.sin_port = htons((uint16_t)PORTNUMBER);
	servAdd.sin_addr.s_addr = inet_addr(IPADDR);

	// bind
	bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));

	// listen
	listen(sd, 5);

	while(1) {  /* reach here for every new connection */

		// accept
		client = accept(sd, (struct sockaddr*)NULL, NULL);

		// get date-time
		printf("Got a date/time request\n");
		currentUnixTime = time(NULL);
		myTime = ctime(&currentUnixTime);

		// send info to client
		send(client, myTime, strlen(myTime) + 1, 0);
		printf("Date and Time sent\n");
	}
	close(client);

}