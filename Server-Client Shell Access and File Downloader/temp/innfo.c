STEPS to be done to make connnection
 	1. socket()  is to be formed
 	2. creating Socket address : either sockaddr_in or sockaddr_un
 	3. i> server-side - binding them with bind()
 	  ii> client-side - connecting them with connect()


About sockaddr_in/sockaddr_un
	making a struct  of type sockaddr_in/sockaddr_un (depending on type of connection)
	struct sockaddr_in serversocketaddress;
    serversocketaddress.sin_family = AF_INET;
    serversocketaddress.sin_port = htons(PORT_NUM);
    serversocketaddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRS);
    serversockaddr_len = sizeof(serversocketaddress);



About socket()
    /*
     * 1st parameter tells about type of connection to make
     *      AF_INET, AF_INET6 : for internet
     *      AF_UNIX, AF_LOCAL : for same machine
     * 2nd parameter is about type of communication to have
     *      SOCK_STREAM : TCP connection
     *      SOCK_DGRAM  : UDP connectionless
     * 3rd parameter  specifies a particular protocol to be used with the socket.
     *      0 : usually set to 0, means 'use the correct and default protocol'

    */
    serversockid1 = socket(AF_INET, SOCK_STREAM, 0);



About bind()
	bind() is written on server side of script

	                                                  ____ sizeof( इसका ) ___
		  socket() का return                        /\                      |
	               |                                  |                       |
	               |                                  |                       |
	               |                                  |                       |
	              \/                                  |                      \/
	bind(serversocketid1, (struct sockaddr *)&server_socket_address, server_address_size);




About connect()
	connect is written on client side of script
	                                                  ____ sizeof( इसका ) ___
		  socket() का return                        /\                      |
	               |                                  |                       |
	               |                                  |                       |
	               |                                  |                       |
	              \/                                  |                      \/
	connect(clientsocketid, (struct sockaddr *)&client_socket_address, client_address_size);




// checker
if( socket() == -1) {
	// error in forming socket
}

if (connect() == -1) {
	// error in making connection
}