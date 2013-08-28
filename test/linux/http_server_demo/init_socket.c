#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "init_socket.h"

int init_socket(int *listen_fd, struct sockaddr_in *server_addr) {
    if ((*listen_fd = socket))
}
