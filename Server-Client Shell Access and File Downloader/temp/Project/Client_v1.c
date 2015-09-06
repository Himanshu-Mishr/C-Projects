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

int main()  {
    int clientSockId;
    int serverSockAddr_len;
    char out_buf[100];
    char in_buf[100];
    memset(&out_buf[0], 0, sizeof(out_buf));
    memset(&in_buf[0], 0, sizeof(in_buf));

    char serverUsername[50];
    memset(&serverUsername[0], 0, sizeof(serverUsername));
    char clientUsername[50];
    memset(&clientUsername[0], 0, sizeof(clientUsername));
    struct sockaddr_in serverSocketAddress;

    // socket
    if ((clientSockId = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error while creating socket");
        exit(1);
    }

    serverSocketAddress.sin_family = AF_INET;
    serverSocketAddress.sin_port = htons(PORT_NUM);
    serverSocketAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRS);
    serverSockAddr_len = sizeof(serverSocketAddress);

    printf("Client: Requesting to server... \n");

    // wait for 2 second
    sleep(2);

    // connect
    if (connect(clientSockId, (struct sockaddr *)&serverSocketAddress, serverSockAddr_len) < 0) {
        perror("Error during connect().");
        exit(1);
    }

    printf("Info: To exit enter(any one) : exit/Exit/kill/bye/logout .\n");

    // accept username from server
    recv(clientSockId, serverUsername, sizeof(serverUsername), 0);

    // send username to server
    getlogin_r(clientUsername, sizeof(clientUsername));
    send(clientSockId, clientUsername, (strlen(clientUsername)+1), 0);

    pid_t pid=fork();
    if (pid < 0) {
        perror("Error during fork()");
        exit(1);
    }
    if (pid) {
        while (1) { /* read output from server */
            recv(clientSockId, in_buf, sizeof(in_buf), 0);
            printf("\n[%s -->] %s\n",clientUsername, in_buf);
            // printf("DEBUGGIN in_buf: %s\n", in_buf);
            /* To exit chat */
            if( strcmp(in_buf, "exit") == 0 ||
                strcmp(in_buf, "Exit") == 0 ||
                strcmp(in_buf, "kill") == 0 ||
                strcmp(in_buf, "logout") == 0)  {
                printf("\n[%s -->] Logged out from chat.\n",serverUsername);
                kill(pid, SIGTERM);
                exit(0);
            }
        }
    }
    else{
        while (1) {  /*read command from client/stdin and send it*/
            printf("\n[%s <--] ", serverUsername);
            fgets(out_buf, sizeof(out_buf),stdin);
            out_buf[strlen(out_buf)-1] = '\0';
            send(clientSockId, out_buf, (strlen(out_buf)+1), 0);

            // printf("DEBUGGIN out_buf: %s\n", out_buf);
            /* To exit chat */
            if( strcmp(out_buf, "exit") == 0 ||
                strcmp(out_buf, "Exit") == 0 ||
                strcmp(out_buf, "kill") == 0 ||
                strcmp(out_buf, "logout") == 0)  {
                printf("\n[%s <--] Logged out from chat.\n",clientUsername);
                kill(pid, SIGTERM);
                exit(0);
            }
        }
    }
    close(clientSockId);
}