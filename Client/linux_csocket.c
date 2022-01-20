#ifdef __linux__
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "lnftw.h"
#include "linux_csoket.h"
#include <pthread.h>
#define SIZE 256 //Max size buffer is 256
#define PORT 8080
#define ADDR "127.0.0.1"


int createSocket(int domain, int type, int protocol)
{
   int socketfd = socket(domain, type, protocol);
 
   if(socketfd == -1)
   {
      perror("Socket error...");
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("Socket successfully created..\n" );
   }
   return socketfd;
}

int Connect(int client_socket, int connect_socket,struct sockaddr_in *ptr_hints)
{
   memset(ptr_hints ,0,sizeof(*ptr_hints));
   // Assign INFO
   ptr_hints->sin_family = AF_INET;
   ptr_hints->sin_port = htons(PORT);
   ptr_hints->sin_addr.s_addr = inet_addr(ADDR);

   connect_socket = connect(client_socket,(struct sockaddr*) ptr_hints, sizeof(*ptr_hints));

   if(connect_socket == -1)
   {
      perror("Connection with the server is failed...\n");
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("Connection is successfully...\n");
   }
   return connect_socket;
}


void searchDirName(int client_socket)
{ 
   char buffer[SIZE]= {0};
   char r_buffer[SIZE]= {0};
   char *p = (char*) calloc(SIZE,sizeof(char));
   pthread_t thread1;

   read(client_socket, r_buffer, SIZE);
   printf("Server msg: %s \n",r_buffer);

   //replay with "processing" each 500ms of searching
   pthread_create(&thread1,NULL,sendMsg,&client_socket); 
   
   if(getDirPath(p, r_buffer) == 1)
   {
      strcpy(buffer, p);
   }
   else
   {
      strcpy(buffer, "Failure");
   }

   pthread_detach(thread1); 
   write(client_socket, buffer,strlen(buffer) + 1);
   printf("Message sent...\n");
   strcpy(buffer,"\\stop");
   write(client_socket, buffer,strlen(buffer) + 1);
   printf("Request to stop listening...\n");
   free(p);
   p = NULL;

}

void closeClientConnection(int client_socket, int connect_socket)
{
   close(client_socket);
   close(connect_socket);
   printf("Client is disconect...\n");
}

#endif