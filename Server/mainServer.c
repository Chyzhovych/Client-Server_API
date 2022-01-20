#ifdef __linux__
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "linux_socket.h"

#elif _WIN32
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "windows_socket.h"

#else 
#error "OS not supported!"
#endif

int main()
{
    #ifdef __linux__
    struct sockaddr_in hints;
    socklen_t addrlen = sizeof(hints);
    int server_socket = 0;
    int client_socket = 0;

    // Create socket

    server_socket = initSocket(&hints);

    // Create new socket descriptor

    client_socket = Accept(server_socket,&hints,&addrlen);

    // Query the directory name to search

    askDir(client_socket);

    // Client response to the request
   
    showDirectoryName(client_socket);

    closeServerConnection(server_socket,client_socket);

    #elif _WIN32

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

    #endif

    return 0;
    
}







