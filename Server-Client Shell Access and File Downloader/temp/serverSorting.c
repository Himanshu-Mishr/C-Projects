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
#define  COUNT 5

// function prototype
void sortdata(int *);

int main() {
    int serversocketid1, serversocketid2;
    int server_address_size, client_address_size;
    int *out_int_buf;
    int *in_int_buf;
    int x, temp;

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

    printf("\n Server is waiting for Client Response ... \n");

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
    printf("\nClient Request is accepted by Server.\n");

    printf("\n Waiting for data from client ... ");

    // initialising input buffer
    in_int_buf = (int *)calloc(COUNT, sizeof(int));

    recv(serversocketid2,(char *)in_int_buf, COUNT*sizeof(int), 0);

    printf("\nData received from client ... as follows ...");

    for (x = 0; x < COUNT; ++x)  {
        printf(" %i ", in_int_buf[x]);
    }
    printf("\n");

    // Sort the received numbers by calling sortdata() function
    sortdata(in_int_buf);

    printf("\n Data Sorted ... Enter any key to send the sorted data back to client ...");
    getchar();

    send(serversocketid2, (char*)in_int_buf, COUNT*sizeof(int), 0);

    printf("\n Data sent back to client after sorting ... \n");

    close(serversocketid1);
    close(serversocketid2);
    return 0;
}

void sortdata(int* in_int_buf)  {
    int j, k, temp;
    for (j = 0; j < 4; ++j)  {
        for (k = j+1; k < 5; ++k)  {
            if(in_int_buf[j] > in_int_buf[k])  {
                temp = in_int_buf[k];
                in_int_buf[k] = in_int_buf[j];
                in_int_buf[j] = temp;
            }
        }
    }
}
