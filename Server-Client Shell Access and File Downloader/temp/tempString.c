#include <stdio.h>
#include <string.h>
#include <unistd.h>

char exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    char result[] = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		strcat(result, buffer);
    }
    pclose(pipe);
    return result;
}

int main() {
	char a[] = "himanshu";
	printf("%s\n", a);
	if(strcmp(a, "himanshu") == 0)
		printf("They both are equal\n");

    // send user/system name
    char username[50];
    getlogin_r(username, sizeof(username));
    printf("Username :  |%s|\n", username);

    char arr[10] = "ls";
    char newArr[1000] = *exec(arr);
    printf("SHELL OUTPUT : %s\n", a);
	return 0;
}