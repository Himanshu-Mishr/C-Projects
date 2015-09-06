// coder   : Himanshu Mishra
// Program : TCP Client

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

#define PORT_NUM 7050
#define SERVER_IP_ADDRS "127.0.0.1"
// #define SERVER_IP_ADDRS "193.106.164.255"

int main()  {    int clientsockid;
    int serversockaddr_len;

    int count=0;

    char out_buf[100];
    char in_buf[100];
    char serverUsername[50];
    memset(&serverUsername[0], 0, sizeof(serverUsername));
    char clientUsername[50];
    memset(&clientUsername[0], 0, sizeof(clientUsername));

    struct sockaddr_in serversocketaddress;

    clientsockid = socket(AF_INET, SOCK_STREAM, 0);

    serversocketaddress.sin_family = AF_INET;
    serversocketaddress.sin_port = htons(PORT_NUM);
    serversocketaddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRS);
    serversockaddr_len = sizeof(serversocketaddress);

    printf("Client: Requesting to server... \n");

    // wait for 2 second
    sleep(2);

    connect(clientsockid, (struct sockaddr *)&serversocketaddress, serversockaddr_len);

    printf("Info: To exit enter(any one) : exit/Exit/kill/bye/logout .\n");

    // accept username from server
    recv(clientsockid, serverUsername, sizeof(serverUsername), 0);

    // send username to server
    getlogin_r(clientUsername, sizeof(clientUsername));
    send(clientsockid, clientUsername, (strlen(clientUsername)+1), 0);

    while (1)  {
        recv(clientsockid, in_buf, sizeof(in_buf), 0);
        printf("%s > %s\n",serverUsername, in_buf);

        printf("%s > ", clientUsername);
        fgets(out_buf, sizeof(out_buf),stdin);
        out_buf[strlen(out_buf)-1] = '\0';

        send(clientsockid, out_buf, (strlen(out_buf)+1), 0);
        // printf("Lenght of message : %lu\n", strlen(out_buf));

        if( strcmp(out_buf, "exit") == 0 ||
            strcmp(out_buf, "Exit") == 0 ||
            strcmp(out_buf, "kill") == 0 ||
            strcmp(out_buf, "bye") == 0  ||
            strcmp(out_buf, "logout") == 0)  {
            break;
        }

    }
    close(clientsockid);
    return 0;
}