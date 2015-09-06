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
#define SERVER_IP_ADDRS "127.0.0.1"

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
    // char  filename[20], /* name of the file to use  */
    //       in_buf[100],  /* buffer*/
    //       acknowledegment[100];  /* buffer use for conformation signal*/

    // printf("\n#INFO : Connection Established.");

    // // receiving filename
    // recv(clientsockid, filename, sizeof(filename), 0);
    // printf("\n#INFO : Receiving filename : %s\n", filename);

    // while (1)  {
    //     printf("\n#INFO : in the loop");
    //     // SIGNAL RECEIVE
    //     recv(clientsockid, acknowledegment, sizeof(acknowledegment), 0);
    //     printf("\n#INFO : received the acknowledegment");
    //     printf("\n acknowledegment received is  %s   ", acknowledegment);

    //     // if acknowledegment is OK then proceed
    //     //if(acknowledegment[0] == 'O' && acknowledegment[1] == 'K') {
    //         printf("\n#INFO : acknowledegment received is OK");
    //         // DATA RECEIVE
    //         recv(clientsockid, in_buf, sizeof(in_buf), 0);
    //         printf("\n#INFO : received the word");
    //         printf("%s", in_buf);

    //         // sening received conformation
    //         strcpy(acknowledegment, "RECEIVED");
    //         send(clientsockid, acknowledegment, (strlen(acknowledegment)+1), 0);
    //     //}
    //     //else
    //     //    break;
    // }
    printf("\n#INFO : CONNECTED TO SERVER ... ");
    FILE *outputFile;
    outputFile = fopen("output.sh", "w");
    char in_buf[100000], ack[100], temp[100000];
    printf("\n#INFO : Person at server entering filename. Please wait...\n");
    printf("\n#INFO : Receviving file ... \n\n");
            recv(clientsockid, in_buf, sizeof(in_buf), 0);
            printf("%s", in_buf);
            fprintf(outputFile, "%s", in_buf);
    // while(1) {
    //         if (in_buf[0] == '@' && in_buf[1] == '@' && in_buf[2]=='L' && in_buf[3] == 'L') {
    //             break;
    //         }

    // }
    printf("EOF");
    printf("\n#INFO : saving with file name : output.txt\n");
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
            printf("%s", out_buf);
            strcat(temp, out_buf);
    }
    send(clientsockid, temp, (strlen(temp)+1), 0);
    fclose(outputFile);
    close(clientsockid);
    return 0;
}

