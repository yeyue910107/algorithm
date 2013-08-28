all : server client
  .PHONY : all
server : server.o
	cc -o server server.o
client : client.o
	cc -o client client.o
client.o : client.c
	cc -g -c client.c
server.o : server.c
	cc -g -c server.c
clean :
	rm server server.o
	rm client client.o

