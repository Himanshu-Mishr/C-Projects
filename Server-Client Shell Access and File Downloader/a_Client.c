#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

#define PORT_NUM 5050
#define SERVER_IP_ADDRS "127.0.0.1"

int main()  {
    int clientSockId;
    int serverSockAddr_len, n;
    char out_buf[1023];
    char in_buf[1023];
    memset(&out_buf[0], 0, sizeof(out_buf));
    memset(&in_buf[0], 0, sizeof(in_buf));

    char serverUsername[50];
    memset(&serverUsername[0], 0, sizeof(serverUsername));
    char clientUsername[50];
    memset(&clientUsername[0], 0, sizeof(clientUsername));
    struct sockaddr_in serverSocketAddress;

    // socket
    if ((clientSockId = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error while creating socket");
        exit(1);
    }

    serverSocketAddress.sin_family = AF_INET;
    serverSocketAddress.sin_port = htons(PORT_NUM);
    serverSocketAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRS);
    serverSockAddr_len = sizeof(serverSocketAddress);

    printf("Client: Requesting to server... \n");

    // wait for 2 second
    sleep(2);

    // connect
    if (connect(clientSockId, (struct sockaddr *)&serverSocketAddress, serverSockAddr_len) < 0) {
        perror("Error during connect().");
        exit(1);
    }


    char GETME[] = "GETME";
    char getme[] = "getme";
    // variable to make fancy prompt
    char line[1040];
    char pp[1040];
    char prompt[] = " $";
    int pid;
    char cwd[1024];

    // ----------------------------------------------- Fancy Prompt -----------
    // getting servers CWD.
    memset(&cwd[0], 0, sizeof(cwd));    // current working directory
    memset(&line[0], 0, sizeof(line));
    size_t nSize = recv(clientSockId, cwd, sizeof(cwd), 0);
    cwd[nSize-1] = '\0';

    // getting current working directory to show at prompt
    strcat(cwd, prompt);

    // fancy prompt
    memset(&pp[0], 0, sizeof(pp));
    // printf("\e[1;44m message \e[0m\e[1;34m\e[0m\n");
    char x1[] = "\e[1;44m ";
    char x2[] = " \e[0m\e[1;34m\e[0m ";
    strcpy(pp, x1);
    strcat(pp, cwd);
    strcat(pp, x2);
    // ------------------------------------------------------------------------

    while (1) { /* read incoming message from server */
        printf("__________________________________________________________\n");
        printf("Info: To exit enter(any one) : exit/Exit/kill/logout .\n");
        printf("Info: To get a file syntax is: GETME filename\n");


        // writing prompt to stdout
        if(write(fileno(stdout), pp, sizeof(pp)) < 0)
            perror("Error in  writing.");

        fgets(out_buf, sizeof(out_buf),stdin);
        out_buf[strlen(out_buf)-1] = '\0';
        send(clientSockId, out_buf, (strlen(out_buf)+1), 0);
        /* To exit chat */
        if( strcmp(out_buf, "exit") == 0 ||
            strcmp(out_buf, "Exit") == 0 ||
            strcmp(out_buf, "kill") == 0 ||
            strcmp(out_buf, "logout") == 0)  {
            printf("\n[  <--] Logged out.\n");
            break;
        }
        if(strstr(out_buf, getme) != NULL || strstr(out_buf, GETME) != NULL) {
            char *filename = out_buf+6;
            FILE *fp = fopen(filename, "w");
            while(1) {  /* reading server's messages */
                if( (n=read(clientSockId, in_buf, sizeof(in_buf))) ) {
                    in_buf[n] = '\0';
                    fprintf(fp, "%s\n", in_buf);
                    if (n < sizeof(in_buf)) {
                        break;
                    }
                }
            }
            fclose(fp);
        }
        else {
            while(1) {  /* reading server's messages */
                if( (n=read(clientSockId, in_buf, sizeof(in_buf))) ) {
                    in_buf[n] = '\0';
                    printf("%s\n", in_buf);
                    if (n < sizeof(in_buf)) {
                        break;
                    }
                }
            }
        }
    }
    close(clientSockId);
}