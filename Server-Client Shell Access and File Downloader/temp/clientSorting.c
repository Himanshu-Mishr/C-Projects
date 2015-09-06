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
#define COUNT 5

int main()  {
    int clientsocketid;
    int client_address_size;
    int *out_int_buf;
    int *in_int_buf;
    int x, n, count;

    // sockaddr_un is a built-in socket address structure defined in header file.
    // declare socket address structure varible
    struct sockaddr_un client_socket_address;

    // create a socket
    clientsocketid = socket(AF_UNIX, SOCK_STREAM, 0);

    // next two lines initialise the 2 values within the socket address structure
    // variable must match withthte vlaues used for the server socket in the server program
    client_socket_address.sun_family = AF_UNIX;     // socket family

    // name of the socket to be assigned
    strcpy(client_socket_address.sun_path, "server_socket");

    // size of the socket address structure
    client_address_size = sizeof(client_socket_address);

    printf("\n Client is requesting to server ... \n");

    // wait for 2 second
    sleep(2);

    // Request OS to try to establish connection with the socket whose name is
    // server_socket and which is alreaddy existing in memory created by server program
    connect(clientsocketid, (struct sockaddr *)&client_socket_address, client_address_size);

    // connect() returns as soon as connection is established. if server process is not running
    // then connect() aborts. program terminates

    printf("\n Connection Established ...");

    printf("\nEnter %d integer values to be sent to server?", COUNT);

    out_int_buf = (int *)calloc(COUNT, sizeof(int));

    for (n = 0; n < COUNT; ++n)  {
        printf("\nEnter inetger value %d : ", n);
        scanf("%d", &out_int_buf[n]);
    }
    if(n==COUNT-1)  {
        printf("\n ......done ......");
    }

    printf("\n The original numbers as entered by user are ... ");

    for (x = 0; x < 4; ++x)    {
        printf(" %i ", out_int_buf[x]);
    }
    printf("\n");

    fflush(stdout);
    printf("\nData sent to server ...");
    printf("\nWaiting fo rserver to send sorted data ... ");

    send(clientsocketid, (char *)out_int_buf,COUNT*sizeof(int), 0);
    in_int_buf = (int *)calloc(COUNT, sizeof(int));

    //receiving data from server

    recv(clientsocketid, (char *)in_int_buf, COUNT*sizeof(int), 0);
    printf("\n Data received from server ...");
    printf("\n The sorted number are as follows ...\n\n");

    for (x = 0; x < 4; ++x)    {
        printf("\t %i", in_int_buf[x]);
    }
    printf("\n");
    close(clientsocketid);
    return 0;
}
