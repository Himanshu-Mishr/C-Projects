// coder   : Himanshu Mishra
// Program : TCP Server

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

#define PORT_NUM 2030
#define SERVER_IP_ADDRS "127.0.0.1"

int main()  {
    int serversockid1, serversockid2;
    int serversockaddr_len, clientsockaddr_len;

    char in_buf[100];

    int count=0;

    struct in_addr client_ip_addr;

    struct sockaddr_in serversocketaddress;
    struct sockaddr_in clientsocketaddress;

    serversockid1 = socket(AF_INET, SOCK_STREAM, 0);

    serversocketaddress.sin_family = AF_INET;
    serversocketaddress.sin_port = htons(PORT_NUM);
    serversocketaddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRS);
    serversockaddr_len = sizeof(serversocketaddress);

    bind(serversockid1, (struct sockaddr *)&serversocketaddress, serversockaddr_len);

    listen(serversockid1, 5);

    printf("\n#INFO : SERVER IS WATIING FOR CLIENT REQUEST\n");

    clientsockaddr_len = sizeof(clientsocketaddress);

    serversockid2 = accept(serversockid1, (struct sockaddr *)&clientsocketaddress, &clientsockaddr_len);

    memcpy(&client_ip_addr, &clientsocketaddress.sin_addr.s_addr, 4);
    printf("\n#INFO : Connection accepted (IP address of the client = %s Port No = %d)", inet_ntoa(client_ip_addr), ntohs(clientsocketaddress.sin_port));

    // -------------------------------connection established

    // send file
    FILE *file;
    char *out_buf = NULL;
    size_t len;
    char read, filename[100];
    char ack[100];
    printf("\n#INFO : Enter filename to trasnfer :");
    scanf("%s", filename);
    printf("\n");
    file=fopen(filename, "r");
    if (file == NULL)
        return 1;
    strcpy(ack, "OK");
    while ((read = getline(&out_buf, &len, file)) != -1) {
            send(serversockid2, out_buf, (strlen(out_buf)+1), 0);
            printf("%s", out_buf);
            sleep(1);

    }
    strcpy(ack, "@@LL");
    send(serversockid2, ack, (strlen(ack)+1), 0);

    // getfile
    // fclose(in_file);
    close(serversockid1);
    close(serversockid2);
    return 0;
}
