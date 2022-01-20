#ifdef __linux__
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lnftw.h" // lib includes realization for search
#include "linux_csoket.h"


int main()
{
    struct sockaddr_in hints;
    int client_socket = 0; 
    int connect_socket = 0;
  
    client_socket = createSocket(AF_INET,SOCK_STREAM,0);

    connect_socket = Connect(client_socket, connect_socket,&hints);

    searchDirName(client_socket);
    
    closeClientConnection(client_socket,connect_socket);

    return 0;

}

#endif


