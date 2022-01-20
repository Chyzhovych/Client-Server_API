#ifdef _WIN32
#ifndef WINDOWS_SOCKET_H
#define WINDOWS_SOCKET_H


int initSocket(SOCKADDR_IN *ptr_hints);

int Connect(SOCKET clientSocket, struct sockaddr_in *ptr_hints);

void closeClientConnection(SOCKET clientSocket);


#endif //WINDOWS_SOCKET_H
#endif
