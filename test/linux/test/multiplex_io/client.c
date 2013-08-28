#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 10240
#define max(a,b) ((a) > (b) ? (a) : (b))

void handle(int sockfd);

int main(int argc, char **argv) {
    char *server_inet_addr = "127.0.0.1";
    int server_port = 6888;
    char buf[MAXLINE];
    int connfd;
    struct sockaddr_in server_addr;

    if (argc == 2) {
	server_inet_addr = argv[1];
    }
    if (argc == 3) {
	server_inet_addr = argv[1];
	server_port = atoi(argv[2]);
    }
    if (argc > 3) {
	printf("usage: select echo client <ip_address> <port>\n");
	return -1;
    }

    connfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_inet_addr, &server_addr.sin_addr);

    if (connect(connfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
	perror("connect error");
	return -1;
    }
    printf("select echo client\n");
    handle(connfd);
    close(connfd);
    printf("exit\n");
    exit(0);
}

void handle(int connfd) {
    FILE* fp = stdin;
    char send_data[MAXLINE], recv_data[MAXLINE];
    fd_set rset;
    FD_ZERO(&rset);
    int max_fds = max(fileno(fp), connfd) + 1, nread;

    for (;;) {
	FD_SET(fileno(fp), &rset);
	FD_SET(connfd, &rset);

	if (select(max_fds, &rset, NULL, NULL, NULL) == -1) {
	    perror("select error");
	    continue;
	}

	if (FD_ISSET(connfd, &rset)) {
	    nread = read(connfd, recv_data, MAXLINE);
	    if (nread == 0) {
		printf("server close the connection\n");
		break;
	    }
	    else if (nread == -1) {
		perror("read error");
		break;
	    }
	    else {
		write(STDOUT_FILENO, recv_data, nread);
	    }
	}
	if (FD_ISSET(fileno(fp), &rset)) {
	    if (fgets(send_data, MAXLINE, fp) == NULL) {
		break;
	    }
	    write(connfd, send_data, strlen(send_data));
	}
    }
}
