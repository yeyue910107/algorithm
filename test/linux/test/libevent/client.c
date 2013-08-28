#include <sys/socket.h>
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

void on_read(int fd, short event, void *arg) {
    int size;
    char *buf = (char *)malloc(MEM_SIZE);
    memset(buf, 0, MEM_SIZE);
    if ((size = read(fd, buf, MEM_SIZE)) < 0) {
	perror("read error");
	return;
    }
    if (size == 0) {
	free(buf);
	close(fd);
	return;
    }
    printf("receive data: %s, size: %d\n", buf, size);
}

void on_write(int fd, short event, void *arg) {
    char *buf = (char *)malloc(MEM_SIZE);
    memset(buf, 0, MEM_SIZE);
    if (fgets(buf, MEM_SIZE, fd) == NULL) {
	free(buf);
	return;
    }
    else {
	write(*(int *)arg, buf, strlen(buf));
    }
}

int main() {
    const char *server_inet_addr = "127.0.0.1";
    int server_port = PORT;
    char buf[MEM_SIZE];
    int connfd;
    FILE *fp = stdin;
    struct sockaddr_in server_addr;

    connfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_inet_addr, &server_addr.sin_addr);

    if (connect(connfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    perror("connect error");
    return -1;
    }
    
    struct event connect_ev, input_ev;
    base = event_base_new();
    
    event_set(&connect_ev, connfd, EV_READ|EV_PERSIST, on_read, NULL);
    event_base_set(base, &connect_ev);
    event_add(&connect_ev, NULL);

    event_set(&input_ev, fileno(fp), EV_WRITE, on_write, &connfd);
    event_base_set(base, &input_ev);
    event_add(&input_ev, NULL);

    event_base_dispatch(base);

    return 0;
}
