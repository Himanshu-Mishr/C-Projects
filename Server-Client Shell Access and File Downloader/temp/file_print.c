#include <stdio.h>
#include <string.h>

int main() {
    char            name[100], out_buf[100];  /* name of the file to use  */
    FILE           *in_file;    /* file for input */

    printf("Name? ");
    fgets(name, sizeof(name), stdin);

    in_file = fopen("filetransfer.txt", "r");
    while(true) {
        if(feof(in_file)) {
            break;
        }
        fscanf(in_file, "%s", out_buf);
        printf("%s ", out_buf);
    }
    fclose(in_file);

}
