#ifndef LINUX_CSOCKET_H
#define LINUX_CSOCKET_H
#ifdef __linux__

int createSocket(int domain, int type, int protocol);

int Connect(int server_socket, int connect_socket,struct sockaddr_in *ptr_hints);

void searchDirName(int client_socket);

void closeClientConnection(int client_socket, int connect_socket);


#endif // LINUX_CSOCKET_H
#endif 