
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>

#include <event.h>

#define PORT 25341
#define BACKLOG 5
#define MEM_SIZE 1024

struct event_base* base;
struct sock_ev {
    struct event* read_ev;
    struct event* write_ev;
    char* buffer;
};

void free_sock_event(struct sock_ev* ev) {
    event_del(ev->read_ev);
    free(ev->read_ev);
    free(ev->write_ev);
    free(ev->buffer);
    free(ev);
}

void on_write(int fd, short event, void *arg) {
    char *buf = (char *)arg;
    send(fd, buf, strlen(buf), 0);
    free(buf);
}

void on_read(int fd, short event, void *arg) {
    struct event* write_ev;
    int size;
    char *buf = (char *)malloc(MEM_SIZE);
    memset(buf, 0, MEM_SIZE);
    if ((size = recv(fd, buf, MEM_SIZE, 0)) < 0) {
	perror("receive error");
	return;
    }
    if (size == 0) {
	free_sock_event((struct sock_ev*)arg);
	close(fd);
	return;
    }
    
    printf("receive data: %s, size: %d\n", buf, size);
    write_ev = (struct event*)malloc(sizeof(struct event));
    event_set(write_ev, fd, EV_WRITE, on_write, buf);
    event_base_set(base, write_ev);
    event_add(write_ev, NULL);
}

void on_accept(int fd, short event, void *arg) {
    struct sockaddr_in client_addr;
    int newfd, sin_size;
    struct event* read_ev = (struct event*)malloc(sizeof(struct event));
    sin_size = sizeof(struct sockaddr_in);
    newfd = accept(fd, (struct sockaddr*)&client_addr, &sin_size);
    event_set(read_ev, newfd, EV_READ|EV_PERSIST, on_read, read_ev);
    event_base_set(base, read_ev);
    event_add(read_ev, NULL);
}

int main(int argc, char **argv) {
    struct sockaddr_in server_addr;
    int listenfd;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
	perror("socket error");
	exit(-1);
    }

    int opt = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) {
	perror("setsockopt error");
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
    
    if (bind(listenfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0) {
	perror("bind error");
	exit(-1);
    }

    if (listen(listenfd, BACKLOG) < 0) {
	perror("listen error");
	exit(-1);
    }

    struct event listen_ev;
    base = event_base_new();
    event_set(&listen_ev, listenfd, EV_READ|EV_PERSIST, on_accept, NULL);
    event_base_set(base, &listen_ev);
    event_add(&listen_ev, NULL);
    event_base_dispatch(base);

    return 0;
}
