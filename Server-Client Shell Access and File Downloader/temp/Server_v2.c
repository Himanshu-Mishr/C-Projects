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

#define PORT_NUM 5050
#define SERVER_IP_ADDRS "127.0.0.1"

void session(int, char*, char*);
void writer(int *fd, char *argv[]);
void reader(int *fd, char *argv[]);

int main()  {
    int serverSockId1, serverSockId2;
    int serverSockAddr_len;

    struct in_addr client_ip_addr;

    struct sockaddr_in serverSocketAddress;
    struct sockaddr_in clientSocketAddress;

    // send user/system name
    char serverUsername[50];
    memset(&serverUsername[0], 0, sizeof(serverUsername));
    getlogin_r(serverUsername, sizeof(serverUsername));

    /*
     * 1st parameter tells about type of connection to make
     *      AF_INET, AF_INET6 : for Internet
     *      AF_UNIX, AF_LOCAL : for same machine
     * 2nd parameter is about type of communication to have
     *      SOCK_STREAM : TCP connection
     *      SOCK_DGRAM  : UDP connectionless
     * 3rd parameter  specifies a particular protocol to be used with the socket.
     *      0 : usually set to 0, means 'use the correct and default protocol'

    */
    /* Socket */
    if ((serverSockId1 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error while making socket on Server-side");
    }

    serverSocketAddress.sin_family = AF_INET;
    serverSocketAddress.sin_port = htons(PORT_NUM);
    serverSocketAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRS);
    serverSockAddr_len = sizeof(serverSocketAddress);

    printf("Server: Waiting for Client Response... \n");

    /* bind */
    if (bind(serverSockId1, (struct sockaddr *)&serverSocketAddress, serverSockAddr_len) == -1) {
        perror("Error while binding socket on Server-side");
    }

    /* listen */
    if (listen(serverSockId1, 5) == -1) {
        perror("Error in listen() on Server-side");
    }

    while (1) { /*reach here for every new connection*/
        unsigned int clientSockAddr_len = sizeof(clientSocketAddress);
        if ((serverSockId2 = accept(serverSockId1, (struct sockaddr *)&clientSocketAddress, &clientSockAddr_len)) < 0) {
            perror("Error during accept()");
            close(serverSockId2);
            continue;
        }

        // Information about client connected
        printf("\n______________________________________________________________");
        printf("\nServer: Client Request is accepted by Server.");
        memcpy(&client_ip_addr, &clientSocketAddress.sin_addr.s_addr, 4);
        printf("\n#INFO : Connection accepted (IP address of the client = %s Port No = %d)", inet_ntoa(client_ip_addr), ntohs(clientSocketAddress.sin_port));

        /* Sending and receiving username/machine name to display on screen.*/
            // send username to new client
        send(serverSockId2, serverUsername, (strlen(serverUsername)+1), 0);

            // accept username from client
        char clientUsername[50];
        memset(&clientUsername[0], 0, sizeof(clientUsername));
        recv(serverSockId2, clientUsername, sizeof(clientUsername), 0);

        if (!fork())
            session(serverSockId2, serverUsername, clientUsername);
        close(serverSockId2);
    }
    close(serverSockId1);
    return 0;
}


void session(int serverSock, char *serverUsername, char *clientUsername) {

    char out_buf[100];
    char in_buf[100];
    memset(&out_buf[0], 0, sizeof(out_buf));
    memset(&in_buf[0], 0, sizeof(in_buf));

    pipe(fd);
    if(!fork())
        reader(fd, argv);  // child
    else
        writer(fd, argv);  // parent


}

void writer(int *fd, char *argv[]) {
    // close read side
    close(fd[0]);

    // all stdout operation will be directed to fd[0];
    dup2(fd[1], 1);

    // after referring it. Now close it. From now onwards output will
    // be written into fd[1] directly
    close(fd[1]);

    // execute a command
    execlp(argv[1], argv[1], NULL);
}
void reader(int *fd, char *argv[]) {
    // close write side
    close(fd[1]);

    // all stdin operation will be directed from fd[0];
    dup2(fd[0], 0);

    // After referring it. Now close it. From now onwards input will
    // be taken from fd[0] directly
    close(fd[0]);

    // execute a command
    execlp(argv[2], argv[2], NULL);
}