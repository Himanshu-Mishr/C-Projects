#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <mysql/mysql.h>

// connection settings
static char *host  =  "localhost";
static char *user  =  "root";
static char *pass  =  "root";
static char *dbname  =  "brms";

unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag = 0;

// Customer account details
struct customer {
	char id[20];
	char name[20];
	char addr[50];
	char dob[20];
	char phno[20];
	double balance;
	char dateAdded[10];
};

// Function prototype
void clearScreen();
void printWelcomeMessege();
void printOptions();
void addAccount();
void showAccount();
void finish_with_error(MYSQL *con);
void deleteAccount();
void showTrans();
void changeBalance(int);
void searchRocord();
void searchRocordById();
void searchRocordByName();
// Driver Function
int main() {
	char option;
	char line[100], accNo[20];

	clearScreen();
	printWelcomeMessege();
	while(1) {
		printOptions();
		// scanf("%c",&option);
		fgets(line, sizeof(line), stdin);
		sscanf(line,"%c",&option);
		switch (option) {
			case 'A':
			case 'a':
				addAccount();
				break;

			case 'D':
			case 'd':
				// TODO : delete row of respective account
				deleteAccount();
				break;

			case '+':
				changeBalance(1);
				break;

			case '-':
				changeBalance(0);
				break;

			case 'S':
			case 's':
				showTrans();
				char temp1;
				printf("\n\t\t\t\t Press Enter to continue: ");
				scanf("%c", &temp1);
				break;

			case 'C':
			case 'c':
				showAccount();
				char temp;
				printf("\n\t\t\t\t Press Enter to continue: ");
				scanf("%c", &temp);
				break;

			case 'F':
			case 'f':
				searchRocord();
				char temp2;
				printf("\n\t\t\t\t Press Enter to continue: ");
				scanf("%c", &temp2);
				break;


			case 'X':
			case 'x':
				return 0;
				break;

			default:
				printf("\n\t\t\t\t Bad input option!!!");
				printf("\n\t\t\t\t Please enter correct option\n");
				break;
		}
		clearScreen();
	}
	return 0;
}

void searchRocordById() {
	char line[100], accNo[20];
	printf("\n\t\t\t\t Enter Account ID : ");
	fgets(line, sizeof(line), stdin);
	sscanf(line,"%s",accNo);

	//  making connection
	MYSQL *conn;

	conn = mysql_init(NULL);

	// Testing DB -------------------------------------------------------------
	if (!(mysql_real_connect(conn, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}

	// Making Query and Printing DB  ------------------------------------------
	char query[200];
	char *ts = "SELECT * FROM client_info where id='";
	char *tr = "';";
	strcpy(query, ts);
	strcat(query, accNo);
	strcat(query, tr);

	if (mysql_query(conn, query))
		finish_with_error(conn);

	MYSQL_RES *result = mysql_store_result(conn);

	if (result == NULL)
		finish_with_error(conn);

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;
	printf("\n                                                     Information of All Clients \n");
	printf("___________________________________________________________________________________________________________________________________________\n");
	printf("|   Account Number     |    Client Name       |   Mailing Address    |     Date Of Birth    |     Phone Number     | Account Creation Date|\n");
	printf("|----------------------|----------------------|----------------------|----------------------|----------------------|----------------------|\n");
	while ((row = mysql_fetch_row(result)))
	{

		for(int i = 0; i < num_fields; i++)
		{
			printf("| %20s ", row[i] ? row[i] : "NULL");
		}
		printf("|\n");
	}

	printf("|______________________|______________________|______________________|______________________|______________________|______________________|\n");

	mysql_free_result(result);
	mysql_close(conn);
}

void searchRocordByName() {
	char line[100], name[20];
	printf("\n\t\t\t\t Enter Account holder name : ");
	fgets(line, sizeof(line), stdin);
	strcpy(name, line);
	name[strlen(name)-1] = ' ';

	//  making connection
	MYSQL *conn;

	conn = mysql_init(NULL);

	// Testing DB -------------------------------------------------------------
	if (!(mysql_real_connect(conn, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}

	// Making Query and Printing DB  ------------------------------------------
	char query[200];
	char *ts = "SELECT * FROM client_info where name='";
	char *tr = "';";
	strcpy(query, ts);
	strcat(query, name);
	strcat(query, tr);

	if (mysql_query(conn, query))
		finish_with_error(conn);

	MYSQL_RES *result = mysql_store_result(conn);

	if (result == NULL)
		finish_with_error(conn);

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;
	printf("\n                                                     Information of All Clients \n");
	printf("___________________________________________________________________________________________________________________________________________\n");
	printf("|   Account Number     |    Client Name       |   Mailing Address    |     Date Of Birth    |     Phone Number     | Account Creation Date|\n");
	printf("|----------------------|----------------------|----------------------|----------------------|----------------------|----------------------|\n");
	while ((row = mysql_fetch_row(result)))
	{

		for(int i = 0; i < num_fields; i++)
		{
			printf("| %20s ", row[i] ? row[i] : "NULL");
		}
		printf("|\n");
	}

	printf("|______________________|______________________|______________________|______________________|______________________|______________________|\n");

	mysql_free_result(result);
	mysql_close(conn);
}
void searchRocord() {
	char line[100], accNo[20], name[20], searchOption[2];
	printf("\n\t\t\t\t Search by Account ID[I] or Search by Name[N] ? ");
	printf("\n\t\t\t\t Enter your option : ");
	fgets(line, sizeof(line), stdin);
	sscanf(line,"%s",searchOption);
	if (searchOption[0] == 'I' || searchOption[0] == 'i') {
		searchRocordById();
	}
	else {
		if (searchOption[0] == 'N' || searchOption[0] == 'n') {
			searchRocordByName();
		}
		else {
			printf("\n\t\t\t\t Bad input option!!!");
		}
	}
}


void changeBalance(int flag) {

	showTrans();

	if(flag == 1)
		printf("\n\t\t\t\t Enter account number to Deposit money : ");
	else
		printf("\n\t\t\t\t Enter account number to Withdraw money : ");

	char line[100], accNo[20];
	fgets(line, sizeof(line), stdin);
	sscanf(line,"%s",accNo);

	double ammount;
	if(flag == 1)
		printf("\n\t\t\t\t Enter ammount to deposit: ");
	else
		printf("\n\t\t\t\t Enter ammount to Withdraw: ");

	fgets(line, sizeof(line),stdin);
	sscanf(line,"%lf",&ammount);

	// get current balance of this account number
	//  Making Connection to sql DB
	MYSQL *conn;

	conn = mysql_init(NULL);

	if (!(mysql_real_connect(conn, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}

	// Making query
	char query[200];
	char *ts = "SELECT balance FROM account_trans where id='";
	char *tr = "';";
	strcpy(query, ts);
	strcat(query, accNo);
	strcat(query, tr);

	// Printing DB
	if (mysql_query(conn, query))
		finish_with_error(conn);

	MYSQL_RES *result = mysql_store_result(conn);

	if (result == NULL)
		finish_with_error(conn);

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;

	double currentBalance = 0;
	while ((row = mysql_fetch_row(result)))
	{

		for(int i = 0; i < num_fields; i++)
		{
			char *ato = row[i] ? row[i] : "0";
			currentBalance = atof(ato);
			// printf("| %20s ", row[i] ? row[i] : "NULL");
		}
	}

	if (flag == 1)
		currentBalance = currentBalance + ammount;
	else
		currentBalance = currentBalance - ammount;

	printf("Current Balance : %f\n", currentBalance);


	// Update new row in account_trans with balance 0
	// "update student_details set stud_name='".$stud_name."', address='".$address."', contact_no=".$contact_no.", email_id='".$email_id."'  where stud_id='".$stud_id."';";

	// Making query
	char updateQuery[200];
	char *ts_1 = "update account_trans set balance=";
	strcpy(updateQuery, ts_1);
	char output[50];
   	snprintf(output,50,"%f",currentBalance);
	strcat(updateQuery, output);
	char *tr_1 = " where id='";
	strcat(updateQuery, tr_1);
	strcat(updateQuery, accNo);
	char *tt = "';";
	strcat(updateQuery, tt);

	MYSQL *connForUpdate;

	connForUpdate = mysql_init(NULL);

	if (!(mysql_real_connect(connForUpdate, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(connForUpdate), mysql_errno(connForUpdate));
		exit(1);
	}

	if (mysql_query(connForUpdate, updateQuery)) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(connForUpdate), mysql_errno(connForUpdate));
	}
	mysql_close(connForUpdate);

	mysql_free_result(result);
	mysql_close(conn);
}

void showTrans() {

	//  Making Connection to sql DB
	MYSQL *conn;

	conn = mysql_init(NULL);

	if (!(mysql_real_connect(conn, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}

	// Printing DB
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
	printf("|");
	}
	printf("\n\t\t|______________________|______________________|______________________|\n");

	mysql_free_result(result);
	mysql_close(conn);
}

void deleteAccount() {
	// Show account to delete
	showAccount();

	// get account number to be deleted
	char accNo[20], line[100], query[200];
	char *tr = "delete from client_info where id='";
	char *ts = "';";
	strcpy(query, tr);

	printf("\n\t\t\t\t Enter account number to delete : ");
	fgets(line, sizeof(line),stdin);
	strcpy(accNo, line);
	accNo[strlen(accNo)-1] = ' ';
	printf("\n\t\t\t\t Account to be delete : %s \n\n", accNo);

	strcat(query, accNo);
	strcat(query, ts);

	// query to delete ----------------------
	//  Making Connection to sql DB
	MYSQL *conn;

	conn = mysql_init(NULL);

	if (!(mysql_real_connect(conn, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}
	// DELETE a row
	// delete from client_info where id='
	// printf("QUERY : %s\n", query);
	if (mysql_query(conn, query)) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
	}
	mysql_close(conn);


	// Delete row in account_trans
	// "delete from account_trans where item_id='".$id."'";

	// Making query
	char deleteQuery[200];
	char *ts_1 = "delete from account_trans where id='";
	strcpy(deleteQuery, ts_1);

	strcat(deleteQuery, accNo);
	char *tt = "';";
	strcat(deleteQuery, tt);

	MYSQL *connForDelete;

	connForDelete = mysql_init(NULL);

	if (!(mysql_real_connect(connForDelete, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(connForDelete), mysql_errno(connForDelete));
		exit(1);
	}

	if (mysql_query(connForDelete, deleteQuery)) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(connForDelete), mysql_errno(connForDelete));
	}
	mysql_close(connForDelete);


	// show fresh table
	showAccount();
}

// Printing all client information
void showAccount() {

	//  Making Connection to sql DB
	MYSQL *conn;

	conn = mysql_init(NULL);

	if (!(mysql_real_connect(conn, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}

	// Printing DB
	if (mysql_query(conn, "SELECT * FROM client_info"))
		finish_with_error(conn);

	MYSQL_RES *result = mysql_store_result(conn);

	if (result == NULL)
		finish_with_error(conn);

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;
	printf("\n                                                     Information of All Clients \n");
	printf("___________________________________________________________________________________________________________________________________________\n");
	printf("|   Account Number     |    Client Name       |   Mailing Address    |     Date Of Birth    |     Phone Number     | Account Creation Date|\n");
	printf("|----------------------|----------------------|----------------------|----------------------|----------------------|----------------------|\n");
	while ((row = mysql_fetch_row(result)))
	{

		for(int i = 0; i < num_fields; i++)
		{
			printf("| %20s ", row[i] ? row[i] : "NULL");
		}
		printf("|\n");
	}

	printf("|______________________|______________________|______________________|______________________|______________________|______________________|\n");



	mysql_free_result(result);
	mysql_close(conn);
}

// Add new account details to DB
void addAccount() {
	// taking info from user and making query
	char query[200];
	char *t1 = "INSERT INTO client_info VALUES('";
	char *br = "','";
	strcpy(query, t1);

	char line[100];
	struct customer newCustomer;

	printf("\n\t\t\t\t Account Number :");
	fgets(line, sizeof(line),stdin);
	strcpy(newCustomer.id, line);
	newCustomer.id[strlen(newCustomer.id)-1] = ' ';
	strcat(query, newCustomer.id);
	strcat(query, br);

	printf("\n\t\t\t\t           Name : ");
	fgets(line, sizeof(line),stdin);
	strcpy(newCustomer.name, line);
	newCustomer.name[strlen(newCustomer.name)-1] = ' ';
	strcat(query, newCustomer.name);
	strcat(query, br);

	printf("\n\t\t\t\t   Mail Address : ");
	fgets(line, sizeof(line),stdin);
	strcpy(newCustomer.addr, line);
	newCustomer.addr[strlen(newCustomer.addr)-1] = ' ';
	strcat(query, newCustomer.addr);
	strcat(query, br);

	printf("\n\t\t\t\t   Date of Birth : ");
	fgets(line, sizeof(line),stdin);
	strcpy(newCustomer.dob, line);
	newCustomer.dob[strlen(newCustomer.dob)-1] = ' ';
	strcat(query, newCustomer.dob);
	strcat(query, br);

	printf("\n\t\t\t\t   Phone Number : ");
	fgets(line, sizeof(line),stdin);
	strcpy(newCustomer.phno, line);
	newCustomer.phno[strlen(newCustomer.phno)-1] = ' ';
	strcat(query, newCustomer.phno);
	char *br1 = "',";
	strcat(query, br1);

	char *now = "now())";
	strcat(query, now);
	// printf("QUERY : %s\n", query);

	// SAVE NEW ACCOUNT INFORMATION INTO DB
	MYSQL *conn;

	conn = mysql_init(NULL);

	if (!(mysql_real_connect(conn, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}

	if (mysql_query(conn, query)) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
	}
	mysql_close(conn);

	// Insert new row in account_trans with balance 0

	// Making query
	char insertQuery[200];
	char *ts = "insert into account_trans values('";
	char *tr = "', 0.00, now());";
	strcpy(insertQuery, ts);
	strcat(insertQuery, newCustomer.id);
	strcat(insertQuery, tr);

	MYSQL *connForInsert;

	connForInsert = mysql_init(NULL);

	if (!(mysql_real_connect(connForInsert, host, user, pass, dbname, port, unix_socket, flag))) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(connForInsert), mysql_errno(connForInsert));
		exit(1);
	}

	if (mysql_query(connForInsert, insertQuery)) {
		fprintf(stderr, "Error : %s [%d]\n", mysql_error(connForInsert), mysql_errno(connForInsert));
	}
	mysql_close(connForInsert);


}


// Clear the screen
void clearScreen() {
	printf("\e[1;1H\e[2J");
}

// Print Project Logo
void printWelcomeMessege() {
	printf("\n\t\t_________________________________________________________________");
	printf("\n\t\t|\t  ____        _____        __  __        _____  	|");
	printf("\n\t\t|\t |  _ \\      |  __ \\      |  \\/  |      / ____| 	|");
	printf("\n\t\t|\t | |_) |     | |__) |     | \\  / |     | (___   	|");
	printf("\n\t\t|\t |  _ <      |  _  /      | |\\/| |      \\___ \\  	|");
	printf("\n\t\t|\t | |_) |  _  | | \\ \\   _  | |  | |  _   ____) | 	|");
	printf("\n\t\t|\t |____/  (_) |_|  \\_\\ (_) |_|  |_| (_) |_____/  	|");
	printf("\n\t\t|_______________________________________________________________|");
	printf("\n\t\t|        BANKING      RECORD     MANAGEMENT    SYSTEM           |");
	printf("\n\t\t|_______________________________________________________________|");

}

// Print Options
void printOptions() {
	printf("\n\t\t________________________________________________________________");
	printf("\n\t\t|                           Options 				|");
	printf("\n\t\t|_______________________________________________________________|");
	printf("\n\t\t|  	Add New Account (A)     	Delete Account   (D)    |");
	printf("\n\t\t|  	Deposit Balance (+)     	Withdraw Balance (-)    |");
	printf("\n\t\t|  	Show All Record (S)     	Account Details  (C)    |");
	printf("\n\t\t|       Search Record   (F)             Exit             (X)    |");
	printf("\n\t\t|_______________________________________________________________|");
	printf("\n\t\t\t\t Select option : ");
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "Error : %s [%d]\n", mysql_error(con), mysql_errno(con));
  mysql_close(con);
}

