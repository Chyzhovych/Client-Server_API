#ifdef __linux__
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "linux_socket.h"

#define PORT 8080
#define BACKLOG 5
#define SIZE 256 // Max size buffer is 256
#define ADDR "127.0.0.1"

int createSocket(int domain, int type, int protocol);

static void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

static void Listen(int socketfd, int backlog);

int initSocket(struct sockaddr_in *ptr_hints)
{
   int opt = 1;  
   int sockfd = createSocket(AF_INET,SOCK_STREAM,0);
 
   memset(ptr_hints,0,sizeof(ptr_hints));
   ptr_hints->sin_family = AF_INET;
   ptr_hints->sin_port = htons(PORT);
   ptr_hints->sin_addr.s_addr = INADDR_ANY;  

   // Forcefully attaching socket to the port 8080 
   if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
   { 
      perror("setsockopt"); 
      exit(EXIT_FAILURE); 
   } 

   Bind(sockfd,(struct sockaddr*) ptr_hints, sizeof (*ptr_hints));

   Listen(sockfd,BACKLOG);
  
   return sockfd;
}


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

static void Bind(int sockfd, const struct sockaddr *adr, socklen_t addrlen)
{
   int res = bind(sockfd, adr, addrlen);
   if (res == -1) 
   {
      perror("Bind failed");
      exit(EXIT_FAILURE);
   }
}

static void Listen(int socketfd, int backlog)
{
   int res = listen(socketfd, backlog);
   if(res == 0)
   {
      printf("Listening...\n");
   }
   else
   {
      perror("Listening failed...");
      exit(EXIT_FAILURE);
   }
 
}

int Accept(int sockfd, struct sockaddr_in *ptr_hints,socklen_t *addrlen) 
{
   int new_fd;
   new_fd = accept(sockfd,(struct sockaddr*) ptr_hints, addrlen);

   if(new_fd < 0)
   {
      perror("Not accept...");
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("Connection accept...\n");
   }

 return new_fd;
}

void askDir(int new_fd)
{
  char msg[SIZE] = {0};
  printf("Enter a directory name: ");
  scanf("%[^\n]", msg);
  send(new_fd,msg,strlen(msg) + 1,0);
}

void showDirectoryName(int new_fd)
{
   char buff[SIZE] = { 0 };

   while (strcmp(buff, "\\stop") != 0)
   {
      bzero(buff, SIZE);
      int nread = read(new_fd, buff, SIZE);
      if(nread == -1)
      {
         perror("Read failed");
         exit(EXIT_FAILURE);
      }
      if (nread == 0)  
      {
         printf("\nEnd of file");
         break;
      }
      if (strncmp(buff, "\\stop", strlen("\\stop")) != 0)
         printf("Client msg: %s", buff);
   }
} 


void closeServerConnection(int server_socket, int client_socket)
{
   close(client_socket);
   close(server_socket);
   printf("\nServer connection close...\n");  

}

#endif 