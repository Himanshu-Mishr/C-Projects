/*=============================================================================
 | Program Name:  Server-Client Chatting System on same computer(UNIX-based)
 |
 |  Description:  Server-side code
 |
 +-----------------------------------------------------------------------------
 |       Author: Himanshu Mishra
 |       Email : himanshu.m786@gmail.com
 *===========================================================================*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
    int serversocketid1, serversocketid2;
    int server_address_size, client_address_size;
    char out_buf[100];
    char in_buf[100];

    struct sockaddr_un server_socket_address;
    struct sockaddr_un client_socket_address;

    // deleting any socket type file named "server_socket" from disk
    unlink("server_socket");

    // creating a socket in os space
    serversocketid1=socket(AF_UNIX, SOCK_STREAM, 0);

    // next 2 lines initialise socket address stucture with a name and socket address Family
    server_socket_address.sun_family=AF_UNIX;
    strcpy(server_socket_address.sun_path, "server_socket");

    // size of socket address structure
    server_address_size = sizeof(server_socket_address);

    printf("\n\n\t Server is waiting for Client Response ... \n");

    // attaching the address with the created socket. (Now socket has a name)
    bind(serversocketid1, (struct sockaddr *)&server_socket_address, server_address_size);

    // requesting OS to track( listen to ) incoming request from any client process
    // that wants to connect to the server's created socket
    listen(serversocketid1, 5);

    // size of the socket address structure
    // requesting OS to accept any such request from client and forward to the server process.
    // accept() waits till such notification comes from OS
    client_address_size = sizeof(client_address_size);

    serversocketid2 = accept(serversocketid1, (struct sockaddr *) &client_socket_address, &client_address_size);

    // accept returns as soon as connection is established with client by OS after
    // receiving a connection requesting from client. accept function returns another
    // fresh id for the same previously created server socket.
    printf("\n\n\t Client Request is accepted by Server.\n");

    while(1)  {

        // assigning the array
        int a[5] = {0, 0, 0, 0, 0};

        //  message for the user to input
        printf("\n\n\tEnter 5 number for sorting:> ");

        //  input array
        scanf("%d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4]);

        // send(sockfd, buf, len, flags);
        send(serversocketid2, a, 5, 0);


        // server process writes data into the socket. and OS sends data to the
        // client socket sever reads data fro the server if sent b client, otherwise,
        // waits for data to arrive from client
        recv(serversocketid2, a, 5, 0);

        // showing the message
        printf("\n\n\tMessage Received from Client> %d %d %d %d %d\n",a[0], a[1], a[2], a[3], a[4]);
    }

    close(serversocketid1);
    close(serversocketid2);
    return 0;
}

