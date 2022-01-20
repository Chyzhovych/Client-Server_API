#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)
#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#include "windows_socket.h"


#define PORT 8080
#define BACKLOG 10
#define SIZE 512 // Max size buffer is 512
#define ADDR "127.0.0.1"


int initSocket(SOCKADDR_IN *ptr_hints)
{
	WSADATA WsaData;
	WORD DLLVer = MAKEWORD(2, 1);
	SOCKET serverSocket = 0;
	int iWSAStartUp = 0;
	int iWSACleanUp = 0;

	// Winsock version 2.1
	if ((iWSAStartUp = WSAStartup(DLLVer, &WsaData)) != 0)
	{
		fprintf(stderr, "Server: WSAStartup() failed with error %d\n", iWSAStartUp);
		WSACleanup();
		return -1;
	}
	else
	{
		printf("Server: WSAStartup() is OK.\n");
	}

	// Create a socket

	serverSocket = socket(AF_INET, SOCK_STREAM, NULL);
	if (serverSocket == INVALID_SOCKET)
	{
		fprintf(stderr, "Server: socket() failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	memset(ptr_hints, 0, sizeof(*ptr_hints));
	//Fill struct sockaddr_in 
	ptr_hints->sin_family = AF_INET;
	ptr_hints->sin_port = htons(PORT);
	ptr_hints->sin_addr.S_un.S_addr = inet_addr(ADDR);

	Bind(serverSocket,(struct sockaddr*)ptr_hints,sizeof(*ptr_hints));

	Listen(serverSocket, BACKLOG);

	return serverSocket;

}

static void Bind(SOCKET serverSocket,const struct sockaddr* addr,int addrlen)
{
	int stat_bind = bind(serverSocket,addr, addrlen);

	if (stat_bind == SOCKET_ERROR)
	{
		fprintf(stderr, "Server: bind() failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	else
	{
		printf("Server: bind() is OK.\n");
	}
}

static void Listen(SOCKET serverSocket, int backlog)
{
	if (listen(serverSocket, backlog) == SOCKET_ERROR)
	{
		fprintf(stderr, "Server: listen() failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	else
	{
		printf("Server: listen() is OK.\n");
	}
}

int Accept(SOCKET serverSocket, struct sockaddr_in *ptr_hints, int *addrlen)
{
	SOCKET connectSocket = 0;
	connectSocket = accept(serverSocket, ptr_hints, addrlen);
	if (connectSocket < 0)
	{
		perror("Not accept...");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Connection accept...\n");
	}

	return connectSocket;
}

void askDir(SOCKET connectSocket)
{
	char s_buff[SIZE] = { 0 };
	printf("Enter directory name: ");
	scanf("%[^\n]", s_buff);
	//strcpy(s_buff, "replays");
	int send_val = send(connectSocket, s_buff, strlen(s_buff) + 1, NULL);

	if (send_val == SOCKET_ERROR)
	{
		fprintf(stderr, "Server: send() failed: error %d \n", WSAGetLastError());
	}
	else
	{
		printf("Server: send() is OK.\n");
	}
}

void showDirectoryName(SOCKET connectSocket)
{
	char buffer[SIZE] = { 0 };
	while (strcmp(buffer, "\\stop"))
	{
		memset(&buffer,0,SIZE);
		int retval = recv(connectSocket, buffer, sizeof(buffer), NULL);
		if (retval == SOCKET_ERROR)
		{
			fprintf(stderr, "Server: recv() failed: error %d\n", WSAGetLastError());
			closesocket(connectSocket);
		}
		else if (strncmp(buffer, "\\stop", strlen("\\stop")) != 0)
		{
			printf("Client msg: %s", buffer);
		}
	}
}

void closeServerConnection(SOCKET serverSocket, SOCKET connectSocket)
{
	printf("\nServer connection close...\n");
	closesocket(serverSocket);
	closesocket(connectSocket);
}


#endif
