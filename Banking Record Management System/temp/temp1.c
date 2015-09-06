#include <stdio.h>

int main() {
	FILE *fp;
	fp = fopen("customer_db.txt", "r");
	char id[200];
	char name[20];
	char addr[50];
	char phno[20];
	char dateAdded[10];
	while(feof(fp)) {
		fscanf(fp, " %s", id);
		printf("Name : %s\n", id);
	}
	return 0;
}