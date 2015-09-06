#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
int main() {
    FILE *file;
    char *line = NULL, words[100000]={0};
    size_t len;
    char read;
    file=fopen("filetransfer.txt", "r");
    if (file == NULL)
        return 1;
    while ((read = getline(&line, &len, file)) != -1) {
        printf("%s", line);
        strcat(words, line);
    }
    printf("%s", words);
    return 0;
}
