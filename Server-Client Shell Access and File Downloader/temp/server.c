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
// contain UNIX socket address structure Required for connection b/w same computer
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
    if ((serversocketid1=socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Server:Error in forming socket");
    }

    // next 2 lines initialise socket address stucture with a name and socket address Family
    server_socket_address.sun_family=AF_UNIX;
    strcpy(server_socket_address.sun_path, "server_socket");

    // size of socket address structure
    server_address_size = sizeof(server_socket_address);

    printf("Server: Waiting for Client Response... \n");

    // attaching the address with the created socket. (Now socket has a name)
    if (bind(serversocketid1, (struct sockaddr *)&server_socket_address, server_address_size) == -1 ) {
        perror("Server:Error in binding");
    }

    // requesting OS to track( listen to ) incoming request from any client process
    // that wants to connect to the server's created socket
    if (listen(serversocketid1, 5) == -1) {
        perror("Server:Error in listen()");
    }

    // size of the socket address structure
    // requesting OS to accept any such request from client and forward to the server process.
    // accept() waits till such notification comes from OS
    client_address_size = sizeof(client_address_size);

    if ((serversocketid2 = accept(serversocketid1, (struct sockaddr *) &client_socket_address, &client_address_size)) == -1 ) {
        perror("Server:Error in accept()");
    }

    // accept returns as soon as connection is established with client by OS after
    // receiving a connection requesting from client. accept function returns another
    // fresh id for the same previously created server socket.
    printf("Server: Client Request is accepted by Server.\n");

    while(1)  {
        printf("Me: ");
        gets(out_buf);
        send(serversocketid2, out_buf, (strlen(out_buf) + 1), 0);

        // server process writes data into the socket. and OS sends data to the
        // client socket sever reads data fro the server if sent b client, otherwise,
        // waits for data to arrive from client
        recv(serversocketid2, in_buf, sizeof(in_buf), 0);

        // showing the message
        printf("Client: '%s' \n", in_buf);
    }

    close(serversocketid1);
    close(serversocketid2);
    return 0;
}

