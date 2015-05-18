all : ipcm

CC = gcc
CFLAGS = -Wall -Werror -g

ipcm: ipcmanager.o sysv_ipc.o ipclist.o
	$(CC) ipcmanager.o sysv_ipc.o ipclist.o -o ipcm
	
ipcmanager.o: ipcmanager.c
	$(CC) -c ipcmanager.c

sysv_ipc.o: sysv_ipc.c
	$(CC) -c sysv_ipc.c
	
ipclist.o: ipclist.c
	$(CC) -c ipclist.c

install:
	mkdir -p $(HOME)/bin
	cp ./ipcm $(HOME)/bin/
	
clean:
	rm *.o ipcm
