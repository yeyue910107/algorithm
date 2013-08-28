all : server client
  .PHONY : all
server : server.o
	cc -o server server.o -levent
client : client.o
	cc -o client client.o -levent
client.o : client.c
	cc -g -c client.c -levent
server.o : server.c
	cc -g -c server.c -levent
clean :
	rm server server.o
	rm client client.o

