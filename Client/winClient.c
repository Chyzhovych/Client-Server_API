#ifdef _WIN32
#include<stdio.h>
#include<winsock2.h>
#include <windows.h>
#include <string.h>
#include "windows_csocket.h"
#include "win_sdir.h"



int main()
{
	SOCKET clientSocket;
	struct sockaddr_in hints;
	
	clientSocket = initSocket(&hints);
	
	// Connect to remote server

	Connect(clientSocket, &hints);

	// Searching a directory name

	searchDirName(clientSocket);

	// Close connection

	closeClientConnection(clientSocket);
	
	
	return 0;
}

#endif


