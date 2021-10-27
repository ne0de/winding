CC = gcc

all: c s 

c: c.c
	$(CC) c.c  -static -lwinpthread -static-libstdc++ -static-libgcc -lws2_32 -o client

s: s.c
	$(CC) s.c -lws2_32 -o server

rs: server
	windows_server $(ip) $(port)
