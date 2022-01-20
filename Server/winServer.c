#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "windows_socket.h"


int  main()
{

	SOCKET serverSocket = 0;
	SOCKET connectSocket = 0;
	SOCKADDR_IN hints;

	// Create a socket 

	serverSocket = initSocket(&hints);

	// Accept()

	connectSocket = Accept(serverSocket,&hints,NULL);
	
	// Query the directory name to search
	
	askDir(connectSocket);

	// Client response to the request

	showDirectoryName(connectSocket);

	// Close connection 

	closeServerConnection(serverSocket, connectSocket);

	system("pause>>NULL");
	return 0;
}
#endif