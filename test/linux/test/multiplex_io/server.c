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

void handle(int *client_sock_fds, int max_fds, fd_set* p_rset, fd_set* p_allset);

int main(int argc, char **argv) {
    int server_port = 6888, listenq = 1024;
    int listenfd, connfd;
    struct sockaddr_in client_addr, server_addr;
    socklen_t sock_len = sizeof(struct sockaddr_in);
    int nready, nread;
    char buf[MAXLINE];
    int client_sock_fds[FD_SETSIZE];
    fd_set allset, rset;
    int maxfd;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
	perror("socket error");
	return -1;
    }

    int opt = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) {
        perror("setsockopt error");
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(server_port);

    if (bind(listenfd, (struct sockaddr*)&server_addr, sock_len) == -1) {
	perror("bind error");
	exit(-1);
    }

    if (listen(listenfd, listenq) < 0) {
	perror("listen error");
	return -1;
    }

    int i = 0;
    for (i = 0; i < FD_SETSIZE; i++)
	client_sock_fds[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    maxfd = listenfd;

    printf("echo server using select is on, listen on port%d\n", server_port);
    printf("max connection: %d\n", FD_SETSIZE);

    for (;;) {
	rset = allset;
	nready = select(maxfd+1, &rset, NULL, NULL, NULL);
	if (nready < 0) {
	    perror("select error");
	    continue;
	}
	if (FD_ISSET(listenfd, &rset)) {
	    connfd = accept(listenfd, (struct sockaddr*)&client_addr, &sock_len);
	    if (connfd < 0) {
		perror("accept error");
		continue;
	    }
	    sprintf(buf, "accept from %s:%d\n", 
		inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
	    printf(buf, "");

	    for (i = 0; i < FD_SETSIZE; i++) {
		if (client_sock_fds[i] == -1) {
		    client_sock_fds[i] = connfd;
		    break;
		}
	    }
	    if (i == FD_SETSIZE) {
		fprintf(stderr, "too many connections, more than %d\n", FD_SETSIZE);
		close(connfd);
		continue;
	    }
	    if (connfd > maxfd)
		maxfd = connfd;
	    FD_SET(connfd, &allset);
	    if (--nready <= 0)
		continue;
	}
	handle(client_sock_fds, maxfd, &rset, &allset);
    }
}

void handle(int *client_sock_fds, int max_fds, fd_set* p_rset, fd_set* p_allset) {
    int nread, i;
    char buf[MAXLINE];

    for (i = 0; i < max_fds; i++) {
	if (client_sock_fds[i] != -1) {
	    if (FD_ISSET(client_sock_fds[i], p_rset)) {
		nread = read(client_sock_fds[i], buf, MAXLINE);
		if (nread < 0) {
		    perror("read error");
		    close(client_sock_fds[i]);
		    FD_CLR(client_sock_fds[i], p_allset);
		    client_sock_fds[i] = -1;
		    continue;
		}
		if (nread == 0) {
		    printf("client close the connection\n");
		    close(client_sock_fds[i]);
		    FD_CLR(client_sock_fds[i], p_allset);
		    client_sock_fds[i] = -1;
		    continue;
		}

		write(client_sock_fds[i], buf, nread);
	    }
	}
    }
}
