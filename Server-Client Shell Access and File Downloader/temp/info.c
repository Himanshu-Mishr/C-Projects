---------------------------------------
STEPS to be done to make connection
 	1. socket()  is to be formed
 	2. creating Socket address structure: either sockaddr_in or sockaddr_un
 	3. i> server-side - binding them with bind()
 	  ii> client-side - connecting them with connect()
 	4. Server wait for connection, which is processed by accept() after connect() from client


 	  		SERVER SIDE 						CLIENT SIDE

 	  		socket()							socket()
 	  			|									|
 	  		   \|									|
 	  		bind()									|
 	  			|									|
 	  		   \|									|
 	  		listen()								|
 	  			|									|
 	  		   \|	  Server is ready to accept		|
 	  		accept()  & wait for connection			|
 	  												|
												   \|
 	  											connect()
 			------------------------------------------------
 						Connection Established
 							Do the task
 						  read()/write()
 			------------------------------------------------
 				|									|
 			   \|									|
 			back to listening step					|
 			for new connection						|
				|									|
				|								   \|
				|								close()
			   \|
			close()

---------------------------------------
About sockaddr_in/sockaddr_un
	making a struct of type sockaddr_in/sockaddr_un (depending on type of connection)
	and adding information in it. Like TCP/UDP, PORT NO, IP ADDRESS

	EXAMPLE
		struct sockaddr_in serversocketaddress;
	    serversocketaddress.sin_family = AF_INET;               // TCP/UDP
	    serversocketaddress.sin_port = htons(PORT_NUM);         // PORT NO
	    serversocketaddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRS);  // IP ADDRESS of server
	    serversockaddr_len = sizeof(serversocketaddress);

---------------------------------------
About socket()
    1st parameter tells about type of connection to make
          AF_INET, AF_INET6 : for internet
          AF_UNIX, AF_LOCAL : for same machine
    2nd parameter is about type of communication to have
          SOCK_STREAM : TCP connection
          SOCK_DGRAM  : UDP connectionless
    3rd parameter  specifies a particular protocol to be used with the socket.
          0 : usually set to 0, means 'use the correct and default protocol'

    EXAMPLE
    	serversockid1 = socket(AF_INET, SOCK_STREAM, 0);


---------------------------------------
About bind()
	bind() is written on server side of script
	It assigns local protocol address to a socket.
	When a socket is created with socket(), it exist in namespace ( addres family)
	but has no name assigned. bind() request that name pointed to by server_socket_address
	be assigned to socket specified by serversocketid1. ( refer below example)


	EXAMPLE
		                                                  ____ sizeof( इसका ) ___
			  socket() का return                        /\                      |
		               |                                  |                       |
		               |                                  |                       |
		               |                                  |                       |
		              \/                                  |                      \/
		bind(serversocketid1, (struct sockaddr *)&server_socket_address, server_address_size);
												    /\
													 |
			sockaddr_in struct का address(pointer)__|


---------------------------------------
About connect()
	connect is written on client side of script
	It is used by a TCP client to establish a connection with a TCP server.

	EXAMPLE
		                                                  ____ sizeof( इसका ) ___
			  socket() का return                        /\                      |
		               |                                  |                       |
		               |                                  |                       |
		               |                                  |                       |
		              \/                                  |                      \/
		connect(clientsocketid, (struct sockaddr *)&client_socket_address, client_address_size);
												    /\
													 |
			sockaddr_in struct का address(pointer)__|


---------------------------------------
About listen()
	It is only called by a TCP server to accept connections from client socket
	that will issue a connect()
	listen is after socket() and bind()
	It has two parameters:
		1> file descriptor returned by socket()
		2> defines the maximum length to which the queue of pending connections for socket() may grow.
	EXAMPLE

			  socket() का return
		               |
		               |
		               |
		              \/
		listen(serversocketid1, 5);

---------------------------------------
About accept()
	Called by TCP server. It creates new file descriptor with properties of server.
	This step is done after listen().
	EXAMPLE
		                                                  ____ sizeof( इसका ) ___
			  socket() का return                        /\                      |
		               |                                  |                       |
		               |                                  |                       |
		               |                                  |                       |
		              \/                                  |                      \/
		accept(serversockid1, (struct sockaddr *)&clientsocketaddress, &clientsockaddr_len);

---------------------------------------
About pipe():

About kill():
About setbuf():
About signal():
About pause():
About rewind():
About dup2():
About execpl():
read()
write()
fread()
fwrite()
About mkfifo():
open()
close()
unlink()


---------------------------------------
Some ways to handle error:
	same is case for socket(), connect(), bind(), listen(),accept()

		if (connect() == -1) {
			// error in making connection
		}
		else {
			// connect established
			// return value 0 also means success

		}



" use fork so that server is free and child process keeps on executing the client request, as soon as server gets ne request it creates a child process and child process to do all work and parent is free to listen to new client"
this is all info available