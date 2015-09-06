#include <iostream>
#include <mysql.h>
#include <string>
#include <cstdio>

class FFError
{
public:
    std::string    Label;

    FFError( ) { Label = (char *)"Generic Error"; }
    FFError( char *message ) { Label = message; }
    ~FFError() { }
    inline const char*   GetMessage  ( void )   { return Label.c_str(); }
};

using namespace std;

int main()
{
    // --------------------------------------------------------------------
    // Connect to the database

    MYSQL      *MySQLConRet;
    MYSQL      *MySQLConnection = NULL;

    string hostName = "localhost";
    string userId   = "user1";
    string password = "supersecret";

    MySQLConnection = mysql_init( NULL );

    try
    {
        MySQLConRet = mysql_real_connect( MySQLConnection,
                                          hostName.c_str(),
                                          userId.c_str(),
                                          password.c_str(),
                                          NULL,  // No database specified
                                          0,
                                          NULL,
                                          0 );

        if ( MySQLConRet == NULL )
            throw FFError( (char*) mysql_error(MySQLConnection) );

        printf("MySQL Connection Info: %s \n", mysql_get_host_info(MySQLConnection));
        printf("MySQL Client Info: %s \n", mysql_get_client_info());
        printf("MySQL Server Info: %s \n", mysql_get_server_info(MySQLConnection));

    }
    catch ( FFError e )
    {
        printf("%s\n",e.Label.c_str());
        return 1;
    }


    // --------------------------------------------------------------------
    //  Create database

    if (mysql_query(MySQLConnection, "CREATE DATABASE adams"))
    {
        printf("Error %u: %s\n", mysql_errno(MySQLConnection), mysql_error(MySQLConnection));
        return(1);
    }

    // --------------------------------------------------------------------
    //  Now that database has been created set default database

    if (mysql_query(MySQLConnection, "USE adams") )
    {
        printf("Error %u: %s\n", mysql_errno(MySQLConnection), mysql_error(MySQLConnection));
        return(1);
    }

    // --------------------------------------------------------------------
    //  Create table and records

    if (mysql_query(MySQLConnection, "CREATE TABLE family (Name char(20),Room char(8),Phone char(24))") )
    {
        printf("Error %u: %s\n", mysql_errno(MySQLConnection), mysql_error(MySQLConnection));
        return(1);
    }

    if (mysql_query(MySQLConnection, "INSERT INTO family VALUES ('Gomez Adams', 'master', '1-555-1212')") )
    {
        printf("Error %u: %s\n", mysql_errno(MySQLConnection), mysql_error(MySQLConnection));
        return(1);
    }

    // --------------------------------------------------------------------
    // Close datbase connection

    mysql_close(MySQLConnection);

    return 0;
}