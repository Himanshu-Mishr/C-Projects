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

#define PORT_NUM 8060
#define SERVER_IP_ADDRS "193.106.164.255"
// #define SERVER_IP_ADDRS "127.0.0.1"

int main()  {
    int serversockid1, serversockid2;
    int serversockaddr_len;
    unsigned int clientsockaddr_len;

    char out_buf[100];
    char in_buf[100];

    int count=0;

    struct in_addr client_ip_addr;

    struct sockaddr_in serversocketaddress;
    struct sockaddr_in clientsocketaddress;

    // send user/system name
    char serverUsername[50];
    memset(&serverUsername[0], 0, sizeof(serverUsername));
    getlogin_r(serverUsername, sizeof(serverUsername));

    /*
     * 1st parameter tells about type of connection to make
     *      AF_INET, AF_INET6 : for internet
     *      AF_UNIX, AF_LOCAL : for same machine
     * 2nd parameter is about type of communication to have
     *      SOCK_STREAM : TCP connection
     *      SOCK_DGRAM  : UDP connectionless
     * 3rd parameter  specifies a particular protocol to be used with the socket.
     *      0 : usually set to 0, means 'use the correct and default protocol'

    */
    if ((serversockid1 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error while making socket on Server-side");
    }

    serversocketaddress.sin_family = AF_INET;
    serversocketaddress.sin_port = htons(PORT_NUM);
    serversocketaddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRS);
    serversockaddr_len = sizeof(serversocketaddress);

    printf("Server: Waiting for Client Response... \n");

    if (bind(serversockid1, (struct sockaddr *)&serversocketaddress, serversockaddr_len) == -1) {
        perror("Error while binding socket on Server-side");
    }


    if (listen(serversockid1, 5) == -1) {
        perror("Error in listen() on Server-side");
    }

    clientsockaddr_len = sizeof(clientsocketaddress);

    while ((serversockid2 = accept(serversockid1, (struct sockaddr *)&clientsocketaddress, &clientsockaddr_len)) != -1) {

        printf("\n______________________________________________________________");
        printf("\nServer: Client Request is accepted by Server.");

        memcpy(&client_ip_addr, &clientsocketaddress.sin_addr.s_addr, 4);
        printf("\n#INFO : Connection accepted (IP address of the client = %s Port No = %d)", inet_ntoa(client_ip_addr), ntohs(clientsocketaddress.sin_port));

        // send username to new client
        send(serversockid2, serverUsername, (strlen(serverUsername)+1), 0);

        // accept username from client
        char clientUsername[50];
        memset(&clientUsername[0], 0, sizeof(clientUsername));
        recv(serversockid2, clientUsername, sizeof(clientUsername), 0);

        while (1)  {
            // printf("\n Enter your Message to be sent to client> ");
            printf("\n%s > ", serverUsername);
            fgets(out_buf, sizeof(out_buf),stdin);
            out_buf[strlen(out_buf)-1] = '\0';

            send(serversockid2, out_buf, (strlen(out_buf)+1), 0);

            recv(serversockid2, in_buf, sizeof(in_buf), 0);

            printf("%s > %s",clientUsername, in_buf);

            if( strcmp(in_buf, "exit") == 0 ||
                strcmp(in_buf, "Exit") == 0 ||
                strcmp(in_buf, "kill") == 0 ||
                strcmp(in_buf, "logout") == 0)  {
                printf("\n%s > Logged out from chat.",clientUsername);
                printf("\n______________________________________________________________");
                printf("\nServer: Waiting for new connection...");
                break;
            }

        }
        close(serversockid2);

    }
    close(serversockid1);
    return 0;
}

