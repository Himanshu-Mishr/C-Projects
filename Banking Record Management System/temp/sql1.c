#include <stdio.h>

int main() {

	// EXEC SQL CONNECT TO mydb@sql.mydomain.com;

	// EXEC SQL CONNECT TO 'unix:postgresql://sql.mydomain.com/mydb' AS myconnection USER john;

	// EXEC SQL BEGIN DECLARE SECTION;
	// const char *target = "mydb@sql.mydomain.com";
	// const char *user = "john";
	// EXEC SQL END DECLARE SECTION;

	// EXEC SQL CONNECT TO :target USER :user;








	return 0;

}