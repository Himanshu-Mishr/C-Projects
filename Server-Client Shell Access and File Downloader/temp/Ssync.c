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
#define SERVER_IP_ADDRS "100.96.221.208"

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
    /**

        TODO:
        - accepts a file name
        - exchanges info before file transfer
        - optional : show progress bar in %

    **/
    // send function ---------------------------------------------
    //   send(int sockfd, const void *buf, size_t len, int flags);
    //   send(serversockid2, out_buf, (strlen(out_buf)+1), 0);
    // receive function ------------------------------------------
    //   recv(int sockfd, void *buf, size_t len, int flags);
    //   recv(serversockid2, in_buf, sizeof(in_buf), 0);
    // printf("\n#INFO : Connection Established.");
    // char  filename[20], /* name of the file to use  */
    //       out_buf[100],  /* buffer*/
    //       acknowledegment[100];   /* buffer use for conformation acknowledegment*/
    // FILE  *in_file;    /* file for input */

    // printf("\nEnter Name of file ? ");
    // fgets(filename, sizeof(out_buf), stdin);

    // in_file = fopen("filetransfer.txt", "r");

    // // sending the file name
    // send(serversockid2, filename, (strlen(filename)+1), 0);

    // while(1) {
    //     // if end of line then acknowledegment and break
    //     printf("\n#INFO : in the loop");
    //     if(feof(in_file)) {
    //         printf("\n#INFO : in the feof ");
    //         // acknowledegment
    //         strcpy(acknowledegment, "STOP");
    //         send(serversockid2, acknowledegment, (strlen(acknowledegment)+1), 0);
    //         break;
    //     }

    //     // acknowledegment
    //     strcpy(acknowledegment, "OK");
    //     printf("\n#INFO : acknowledegment send");
    //     send(serversockid2, acknowledegment, (strlen(acknowledegment)+1), 0);

    //     // data read and send
    //     fscanf(in_file, "%s", out_buf);
    //     send(serversockid2, out_buf, (strlen(out_buf)+1), 0);
    //     printf("\n ---> %s", out_buf);
    //     printf("\n#INFO : send the words");

    //     // received conformation
    //     recv(serversockid2, acknowledegment, sizeof(acknowledegment), 0);
    //     if(strcmp(acknowledegment, "RECEIVED"))
    //         printf("\n#INFO : acknowledegment received .. continuing further");
    // }
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
            recv(serversockid2, ack, sizeof(ack), 0);
    }
    strcpy(ack, "@@LL");
    send(serversockid2, ack, (strlen(ack)+1), 0);

    // fclose(in_file);
    close(serversockid1);
    close(serversockid2);
    return 0;
}
