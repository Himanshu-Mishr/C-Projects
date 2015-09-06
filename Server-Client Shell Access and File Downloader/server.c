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

void child(int);

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
    /* Step 1: forming Socket */
    if ((serverSockId1 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error while making socket on Server-side");
    }

    serverSocketAddress.sin_family = AF_INET;
    serverSocketAddress.sin_port = htons(PORT_NUM);
    serverSocketAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRS);
    serverSockAddr_len = sizeof(serverSocketAddress);

    printf("Server: Waiting for Client Response... \n");

    /* Step 2: binding configuration */
    if (bind(serverSockId1, (struct sockaddr *)&serverSocketAddress, serverSockAddr_len) == -1) {
        perror("Error while binding socket on Server-side");
    }

    /* Step 3: Sever listening */
    if (listen(serverSockId1, 5) == -1) {
        perror("Error in listen() on Server-side");
    }

    while (1) { /*reach here for every new connection*/
        unsigned int clientSockAddr_len = sizeof(clientSocketAddress);
        // Step 4: accept new connection.
        if ((serverSockId2 = accept(serverSockId1, (struct sockaddr *)&clientSocketAddress, &clientSockAddr_len)) < 0) {
            perror("Error during accept()");
            close(serverSockId2);
            continue;
        }

        // Information about client connected
        printf("\nServer: Client Request is accepted by Server.");
        memcpy(&client_ip_addr, &clientSocketAddress.sin_addr.s_addr, 4);

        if (!fork())
            child(serverSockId2); /*server create a child process for communication*/
        close(serverSockId2);
    }
    close(serverSockId1);
    return 0;
}

// Handles communication.
void child(int serverSock) {

    // Redirect IO
    dup2(serverSock, 0);  // stdin
    dup2(serverSock, 1);  // stdout
    dup2(serverSock, 2);  // stderr

    char GETME[] = "GETME";
    char getme[] = "getme";
    char out_buf[1000];
    char in_buf[1000];

    // clearing buffer
    memset(&out_buf[0], 0, sizeof(out_buf));
    memset(&in_buf[0], 0, sizeof(in_buf));

    // sending cwd to client for making prompt
    system("pwd");

    while (1) { /* read incoming message from Client */
        recv(serverSock, in_buf, sizeof(in_buf), 0);
        /* To exit chat */
        if( strcmp(in_buf, "exit") == 0 ||
            strcmp(in_buf, "Exit") == 0 ||
            strcmp(in_buf, "kill") == 0 ||
            strcmp(in_buf, "logout") == 0)  {
            kill(getpid(), SIGTERM);
            exit(0);
        }
        // execlp(in_buf, in_buf, NULL);

        if(strstr(in_buf, getme) != NULL || strstr(in_buf, GETME) != NULL) {
            char *filename = in_buf+6;
            char cat[100] = "cat ";
            strcat(cat, filename);
            system(cat);
        }
        else
            system(in_buf);
    }
}
