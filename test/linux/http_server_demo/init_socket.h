#ifndef __INIT_SOCKET_H_
#define __INIT_SOCKET_H_

#include <netinet/in.h>

#define BACKLOG 20
#define PORT 8080

int init_socket(int *listen_fd, struct sockaddr_in *server_addr);

#endif
