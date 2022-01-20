#ifdef _WIN32
#ifndef WINDOWS_SOCKET_H
#define WINDOWS_SOCKET_H


int initSocket(SOCKADDR_IN *ptr_hints);

static void Bind(SOCKET serverSocket, const struct sockaddr* addr, int addrlen);

static void Listen(SOCKET serverSocket, int backlog);

int Accept(SOCKET serverSocket, struct sockaddr_in *ptr_hints, int *addrlen);

void askDir(SOCKET connectSocket);

void showDirectoryName(SOCKET connectSocket);

void closeServerConnection(SOCKET serverSocket, SOCKET connectSocket);


#endif //WINDOWS_SOCKET_H
#endif
