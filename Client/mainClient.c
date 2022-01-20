#ifdef __linux__

#include "linux_csoket.h"
#include "lnftw.h"
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#elif _WIN32

#include "windows_csocket.h"
#include "win_sdir.h"

#else 
#error "OS not supported!"
#endif

int main()
{
    #ifdef __linux__

    struct sockaddr_in hints;
    int client_socket = 0; 
    int connect_socket = 0;

    // Create a socket

    client_socket = createSocket(AF_INET,SOCK_STREAM,0);

    // Connect to remote server

    connect_socket = Connect(client_socket, connect_socket,&hints);

    // Searching a directory name

    searchDirName(client_socket);

    // Close connection
    
    closeClientConnection(client_socket,connect_socket);

    #elif _WIN32
    SOCKET client_socket;
    SOCKADDR_IN hints;

    // Create a socket

    clientSocket = initSocket(&hints);
	
	// Connect to remote server

	Connect(clientSocket, &hints);

	// Searching a directory name

	searchDirName(clientSocket);

	// Close connection

	closeClientConnection(clientSocket);
   
    #endif

    return 0;

}









