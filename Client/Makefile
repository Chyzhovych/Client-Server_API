CC= gcc

CFLAGS=-c

all: crossClient

crossClient: mainClient.o linux_csocket.o lnftw.o win_sdir.o windows_csocket.o
	$(CC) mainClient.o linux_csocket.o lnftw.o win_sdir.o windows_csocket.o -lpthread -o crossClient

mainClient.o: mainClient.c
	$(CC) $(CFLAGS) mainClient.c

lnftw.o: lnftw.c lnftw.h
	$(CC) $(CFLAGS) -lpthread lnftw.c

linux_csocket.o: linux_csocket.c  
	$(CC) $(CFLAGS) -lpthread linux_csocket.c

windows_csocket.o: windows_csocket.c windows_csocket.h
	$(CC) $(CFLAGS) windows_csocket.c

win_sdir.o: win_sdir.c win_sdir.h
	$(CC) $(CFLAGS) win_sdir.c	

clientLinux: 
	$(CC) linuxClient.c linux_csocket.c lnftw.c -lpthread -o clientLinux

clean:
	rm -rf *.o crossClient clientLinux

