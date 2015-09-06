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

#define PORT_NUM 7070
#define SERVER_IP_ADDRS "127.0.0.1"

int main()  {
    int clientsockid;
    int serversockaddr_len;

    int count=0;

    char out_buf[100];
    char in_buf[100];

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

    while (count != 5)  {
        recv(clientsockid, in_buf, sizeof(in_buf), 0);
        printf("\nServer > %s", in_buf);

        printf("\nMe > ");
        // gets(out_buf);
        fgets(out_buf, sizeof(out_buf),stdin);

        send(clientsockid, out_buf, (strlen(out_buf)+1), 0);
        count++;
    }
    close(clientsockid);
    return 0;
}

