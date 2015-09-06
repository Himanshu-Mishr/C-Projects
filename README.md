# C-Projects
My Projects based on C Programming. Application ranges from using MySQL API and UNIX C Libraries.

## Banking Record Management System
This program uses MySQL API in order to maintain banking database. This whole program is automated. It has features that allows user to add/edit/remove customers. It provided easy options and efficiently maintains user accounts and its details.

####Prerequisites
MySQl. You can use `brms.sql` file as database.
####Installation Instruction
$`clang bank.c -o bank -I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing    -g -DNDEBUG -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl`

$`./bank`

## Server-Client Shell Access and File Downloader
This program is a client/server application for the file download between a server and a client. Program allows multiple clients to access server. Program efficiently uses fork, socket, pipe, signal, etc. The client can execute any UNIX utility on the server machine like a remote login. And in addition client can download a file from server.

####Prerequisites
  You need to get server's IP address before compiling and running program.

####Installation Instruction
`server.c` and `client.c` should be executed on respective system. Program can be run on same system but then you have set IP address variable `SERVER_IP_ADDRS` to `127.0.0.1`.
