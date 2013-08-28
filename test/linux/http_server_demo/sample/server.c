#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#include "server.h"

/* http response and header for a successful request */
static char *ok_response = 
  "HTTP/1.0 200 OK\n"
  "Content-type: text/html\n"
  "\n";

/* http response, header and body, indicating that we did not understand the request */
static char* bad_request_response = 
  "HTTP/1.0 400 Bad Request\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  " <body>\n"
  "  <h1>Bad Request</h1>\n"
  "  <p>This server did not understand your request.</p>\n"
  " </body>\n"
  "</html>\n";

/* HTTP response, header, and body template indicating that the
   requested document was not found.  */

static char* not_found_response_template = 
  "HTTP/1.0 404 Not Found\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  " <body>\n"
  "  <h1>Not Found</h1>\n"
  "  <p>The requested URL %s was not found on this server.</p>\n"
  " </body>\n"
  "</html>\n";

/* HTTP response, header, and body template indicating that the
   method was not understood.  */

static char* bad_method_response_template = 
  "HTTP/1.0 501 Method Not Implemented\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  " <body>\n"
  "  <h1>Method Not Implemented</h1>\n"
  "  <p>The method %s is not implemented by this server.</p>\n"
  " </body>\n"
  "</html>\n";


/* handler for SIGCHID, clean up child processes that have terminated */
static void clean_up_child_process(int signal_number) {
    int status;
    wait(&status);
}

/* process an HTTP "GET" request for page, and send the results to the fd */
static void handle_get(int fd, const char *page) {
    struct server_module *module = NULL;

    if (*page == '/' && strchr(page+1, '/') == NULL) {
	char module_file_name[64];
	snprintf(module_file_name, sizeof(module_file_name), 
		"%s.so", page + 1);
	module = module_open(module_file_name);
    }

    if (module == NULL) {
	char response[1024];
	snprintf(response, sizeof(response), not_found_response_template, page);
	write(fd, response, strlen(response));
    }
    else {
	write(fd, ok_response, strlen(ok_response));
	(*module->generate_function)(fd);
	module_close(module);
    }
}

/* handle a client connection on the fd */
static void handle_connection(int fd) {
    char buffer[256];
    ssize_t bytes_read;

    bytes_read = read(fd, buffer, sizeof(buffer)-1);
    if (bytes_read > 0) {
	char method[sizeof(buffer)], url[sizeof(buffer)], protocol[sizeof(buffer)];
	buffer[bytes_read] = '\0';
	sscanf(buffer, "%s%s%s", method, url, protocol);
	while (strstr(buffer, "\r\n\r\n") == NULL)
	    bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read < 0) {
	    close(fd);
	    return;
	}
	if (strcmp(protocol, "HTTP/1.0") && strcmp(protocol, "HTTP/1.1")) {
	    write(fd, bad_request_response, sizeof(bad_request_response));
	}
	else if (strcmp(method, "GET")) {
	    char response[1024];
	    snprintf(response, sizeof(response), bad_method_response_template, method);
	    write(fd, response, strlen(response));
	}
	else
	    handle_get(fd, url);
    }
    else if (bytes_read == 0)
	;
    else
	system_error("read");
}

void server_run(struct in_addr local_addr, uint16_t port) {
    struct sockaddr_in socket_addr;
    int rval;
    struct sigaction sigchld_action;
    int server_socket;

    /* install a handler for SIGCHLD that cleans up child processes that have terminated */
    memset(&sigchld_action, 0, sizeof(struct sigaction));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction(SIGCHLD, &sigchld_action, NULL);

    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
	system_error("socket");
    memset(&socket_addr, 0, sizeof(struct sockaddr_in));
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr = local_addr;
    socket_addr.sin_port = port;

    rval = bind(server_socket, &socket_addr, sizeof(struct sockaddr_in));
    if (rval < 0)
	system_error("listen");
    if (verbose) {
	socklen_t addr_len = sizeof(struct sockaddr_in);
	rval = getsockname(server_socket, &socket_addr, &addr_len);
	assert(rval == 0);
	printf("server listening on %s:%d\n", 
		inet_ntoa(socket_addr.sin_addr), 
		(int)ntohs(socket_addr.sin_port));
    }

    while (1) {
	struct sockaddr_in remote_addr;
	socklen_t addr_len;
	int connection;
	pid_t child_pid;

	addr_len = sizeof(struct sockaddr_in);
	connection = accept(server_socket, &remote_addr, &addr_len);
	if (connection < 0) {
	    if (errno = EINTR)
		continue;
	    else
		system_error("accept");
	}

	if (verbose) {
	    socklen_t addr_len;
	    addr_len = sizeof(struct sockaddr_in);
	    rval = getpeername(connection, &socket_addr, &addr_len);
	    assert(rval == 0);
	    printf("connection accepted from %s\n", 
		inet_ntoa(socket_addr.sin_addr));
	}

	/* fork a child process to handle the connection */
	child_pid = fork();
	if (child_pid == 0) {
	    /* child process, close stdin & stdout & listen socket */
	    close(STDIN_FILENO);
	    close(STDOUT_FILENO);
	    close(server_socket);
	    handle_connection(connection);
	    close(connection);
	    exit(0);
	}
	else if (child_pid > 0) {
	    /* parent process */
	    close(connection);
	}
	else 
	    system_error("fork");
    }
}
