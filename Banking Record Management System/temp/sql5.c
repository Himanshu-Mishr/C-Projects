#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

// connection settings
static char *host  =  "localhost";
static char *user  =  "root";
static char *pass  =  "root";
static char *dbname  =  "brms";

unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag = 0;

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "Error : %s [%d]\n", mysql_error(con), mysql_errno(con));
  mysql_close(con);
  exit(1);
}



int main() {
	printf("Using MySQL client version: %s\n", mysql_get_client_info());

	MYSQL *conn;

	conn = mysql_init(NULL);

	// Testing DB -------------------------------------------------------------
	if (!(mysql_real_connect(conn, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}
	printf("Connection Successful\n");

	// Making Query and Printing DB  ------------------------------------------
	if (mysql_query(conn, "SELECT * FROM account_trans"))
		finish_with_error(conn);

	MYSQL_RES *result = mysql_store_result(conn);

	if (result == NULL)
		finish_with_error(conn);

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;
	printf("\n                   Information of Transaction ");
	printf("\n\t\t______________________________________________________________________");
	printf("\n\t\t|   Account Number     |       Balanc ( ₹ )   | A/c Last Update Date |");
	printf("\n\t\t|----------------------|----------------------|----------------------|");

	while ((row = mysql_fetch_row(result)))
	{
		printf("\n\t\t");
		for(int i = 0; i < num_fields; i++)
		{
			printf("| %20s ", row[i] ? row[i] : "NULL");
		}
	}
	printf("|");
	printf("\n\t\t|______________________|______________________|______________________|\n");

	mysql_free_result(result);
	mysql_close(conn);

	return EXIT_SUCCESS;
}

// How to run the program ?
/**
first run them on command Prompt
mysql_config --cflag  // output 1
mysql_config --libs  // output 2

then add them to this and run
gcc filename.c -o outputFilename output_1 output_2


example , mine in Linux will be :
gcc bank.c -o bank -I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing    -g -DNDEBUG -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl
**/