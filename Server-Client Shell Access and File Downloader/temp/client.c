/*=============================================================================
 | Program Name:  Server-Client Chatting System on same computer(UNIX-based)
 |
 |  Description:  Client-side code
 |
 +-----------------------------------------------------------------------------
 |       Author: Himanshu Mishra
 |       Email : himanshu.m786@gmail.com
 *===========================================================================*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <strings.h>
#include <sys/un.h>
#include <unistd.h>

int main()  {
    int clientsocketid;
    int client_address_size;
    char out_buf[100];
    char in_buf[100];

    // sockaddr_un is a built-in socket address structure defined in header file.
    // declare socket address structure varible
    struct sockaddr_un client_socket_address;

    // create a socket
    if ((clientsocketid = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Client:Error in forming socket");
    }

    // next two lines initialise the 2 values within the socket address structure
    // variable must match withthte vlaues used for the server socket in the server program
    client_socket_address.sun_family = AF_UNIX;     // socket family

    // name of the socket to be assigned
    strcpy(client_socket_address.sun_path, "server_socket");

    // size of the socket address structure
    client_address_size = sizeof(client_socket_address);

    printf("Client: Requesting to server... \n");

    // wait for 2 second
    sleep(2);

    // Request OS to try to establish connection with the socket whose name is
    // server_socket and which is alreaddy existing in memory created by server program
    if (connect(clientsocketid, (struct sockaddr *)&client_socket_address, client_address_size) == -1 ) {
        perror("Client:Error in connect()");
    }

    // connect() returns as soon as connection is established. if server process is not running
    // then connect() aborts. program terminates

    while(1)  {

        // receiving data from the socket into the client program variable if
        // data available in the socket ( if sent by server), otherwise waits.
        recv(clientsocketid, in_buf, sizeof(in_buf), 0);

        // displaying the receivied message from server
        printf("Server: '%s' \n", in_buf);
        printf("Me: ");

        gets(out_buf);

        // writing data from program vairable to the created socket OS
        // automatically sends it to server program's created socket(server socket).
        send(clientsocketid, out_buf, (strlen(out_buf) + 1), 0);
    }
    close(clientsocketid);
    return 0;
}

