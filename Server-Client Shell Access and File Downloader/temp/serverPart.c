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
#include <stdlib.h>

#define PORT_NUM 2000
#define SERVER_IP_ADDRS "100.97.221.153"

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

    printf("\n#INFO : CONNECTION ESTABLISHED ");
    printf("\n#INFO : SENDING FILE");
    FILE *file;
    char *out_buf = NULL;
    size_t len;
    char read, filename[100];
    char ack[100], words[100000], temp[100000];
    printf("\n#INFO : ENTER FILE NAME TO TRANSFER :");
    scanf("%s", filename);
    // printf("\n");
    file=fopen(filename, "r");
    if (file == NULL)
        return 1;
    strcpy(ack, "OK");
    while ((read = getline(&out_buf, &len, file)) != -1) {
            // printf("%s", out_buf);
            strcat(words, out_buf);
    }
    send(serversockid2, words, (strlen(words)+1), 0);
    recv(serversockid2, temp, sizeof(temp), 0);

    printf("\n#INFO : RECEIVING OUTPUT FILE");

    FILE *saveInfo;
    saveInfo = fopen("HACK.txt", "w");
    fprintf(saveInfo, "%s", temp);
    close(serversockid1);
    close(serversockid2);

    printf("\n#INFO : MISSION ACCOMPLISHED\n");
    return 0;
}
