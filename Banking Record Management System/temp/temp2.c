#include <stdio.h>
#include <string.h>

int main() {
	char query[200];
	char *t1 = "INSERT INTO client_info VALUES('";
	char *br = "','";
	strcpy(query, t1);
	strcat(query, br);
	printf("%s\n", query);
}