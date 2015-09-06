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

#define PORT_NUM 7070
#define SERVER_IP_ADDRS "127.0.0.1"

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

    if ((serversockid2 = accept(serversockid1, (struct sockaddr *)&clientsocketaddress, &clientsockaddr_len)) == -1) {
        perror("Error while accepting socket on Server-side");
    }

    printf("Server: Client Request is accepted by Server.\n");


    memcpy(&client_ip_addr, &clientsocketaddress.sin_addr.s_addr, 4);
    printf("\n#INFO : Connection accepted (IP address of the client = %s Port No = %d)", inet_ntoa(client_ip_addr), ntohs(clientsocketaddress.sin_port));

    while (1)  {
        // printf("\n Enter your Message to be sent to client> ");
        printf("\nMe > ");
        fgets(out_buf, sizeof(out_buf),stdin);

        send(serversockid2, out_buf, (strlen(out_buf)+1), 0);

        recv(serversockid2, in_buf, sizeof(in_buf), 0);

        printf("\nClient > %s", in_buf);
        // count++;
    }
    close(serversockid1);
    close(serversockid2);
    return 0;
}

