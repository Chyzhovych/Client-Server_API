#ifndef LINUX_SOCKET_H
#define LINUX_SOCKET_H
#ifdef __linux__
#define SIZE 256 //Max size buffer is 256
#define ADDR "127.0.0.1"

int createSocket(int domain, int type, int protocol);

int initSocket();

int Accept(int sockfd, struct sockaddr_in *ptr_hints,socklen_t *addrlen);

void askDir(int new_fd);

void showDirectoryName(int new_fd);

void closeServerConnection(int server_socket, int client_socket);


#endif // LINUX_SOCKET_H

#endif