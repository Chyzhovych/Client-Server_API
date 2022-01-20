#ifdef _WIN32
#include<stdio.h>
#include<winsock2.h>
#include <windows.h>
#include <string.h>
#include "windows_csocket.h"
#include "win_sdir.h"
#pragma warning(disable: 4996)
#pragma comment(lib,"ws2_32.lib") 

#define ADDR "127.0.0.1"
#define PORT 8080
#define SIZE 512 // Max size a buffer
#define START_SEARCH "C:\\" // The search starts from this directory
#define FAILURE 0

int initSocket(SOCKADDR_IN *ptr_hints)
{
	WSADATA wsa;
	SOCKET clientSocket;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 1), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//Create a socket
	if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	else
	{
		printf("Socket created...\n");
	}

	// Fill struct sockaddr_in

	ptr_hints->sin_addr.s_addr = inet_addr(ADDR);
	ptr_hints->sin_family = AF_INET;
	ptr_hints->sin_port = htons(PORT);

	return clientSocket;
}

int Connect(SOCKET clientSocket, struct sockaddr_in *ptr_hints)
{
	if (connect(clientSocket, (struct sockaddr *)ptr_hints, sizeof(*ptr_hints)) < 0)
	{
		puts("Connect error...");
		return 1;
	}
	puts("Connected");
}


void searchDirName(SOCKET clientSocket)
{
	HANDLE hThread;
	DWORD   dwThreadId;
	char buffer[SIZE] = { 0 };
	char r_buff[SIZE] = { 0 };

	int s_recv = recv(clientSocket, buffer, SIZE, NULL);
	// Check recv data
	if(s_recv == SOCKET_ERROR)
	{
       perror("Recv failed...");
	}
	printf("Client: recv() is OK.\n");
	printf("Serv msg: %s \n", buffer);
	strcpy(r_buff, buffer);

	hThread = CreateThread(NULL, 0, sendMsg, (LPVOID)clientSocket, 0, &dwThreadId);
    
	// Check if hThread is valid 

	if (hThread == NULL) 
    {
        ErrorHandler(TEXT("CreateThread"));
        ExitProcess(3);
    }

	int res = ListDirectoryContents(START_SEARCH, r_buff);
	if (SuspendThread(hThread) == -1) {
		printf("Failure to suspend thread\nStop the process\n\nPress Enter to exit");
		_getch();
		exit(1);
	}
	else if (res == FAILURE)
	{
		strcpy(r_buff, "Failure...");
	}
    // Check send func
	
	if (send(clientSocket, r_buff, strlen(r_buff) + 1, 0) < 0)
	{
		puts("Send failed...");
		return 1;
	}

	const char * stopMsg = "\\stop";
	send(clientSocket, stopMsg, strlen(stopMsg) + 1, 0);

	puts("Data Send...\n");

}

void closeClientConnection(SOCKET clientSocket)
{
	printf("\nClient connection close...\n");
	closesocket(clientSocket);
}

#endif