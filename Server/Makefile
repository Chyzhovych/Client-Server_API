CC= gcc
CFLAGS=-c

all: crossServer serverLinux

crossServer: mainServer.o linux_socket.o windows_socket.o
	$(CC) mainServer.o linux_socket.o windows_socket.o -o crossServer

mainServer.o: mainServer.c
	$(CC) $(CFLAGS) mainServer.c 

linux_socket.o: linux_socket.c linux_socket.h
	$(CC) $(CFLAGS) linux_socket.c

windows_socket.o: windows_socket.c windows_socket.h
	$(CC) $(CFLAGS) windows_socket.c
 	
serverLinux:
	$(CC) linuxServer.c linux_socket.c -o serverLinux

debug_server: linux_socket.h
	$(CC) -g linuxServer.c linux_socket.c -o server.out	

clean:
	rm -rf *.o serverLinux crossServer