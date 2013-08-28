#ifndef __SERVER_H_
#define __SERVER_H_

#include <netinet/in.h>
#include <sys/types.h>

/*** symbols defined in common.c ***/

/* the name of the program */
extern const char *program_name;

/* if nonzero, print verbose messages */
extern int verbose;

/* like malloc, except aborts the program if allocation fails */
extern void *xmalloc(size_t size);


/* like realloc, except aborts the program if allocation fails */
extern void *xrealloc(void *ptr, size_t size);


/* like strdup, except aborts the program if allocation fails */
extern char *xstrdup(const char *s);

/* print an error message for a failed call operation */
extern void system_error(const char *operation);

/* print an error message for a failure involing cause */
extern void error(const char *cause, const char *message);

/* return the directory containing the running program's executable */
extern char *get_self_executable_directory();

/*** symbols defined in module.c ***/

/* an instance of a loaded server module */
struct server_module {
    /* the shared lib handle corresponding to the loaded module */
    void *handle;
    /* module name */
    const char *name;
    /* the function generates the HTML results for this module */
    void (* generate_function)(int);
};

/* the directory from which modules are loaded */
extern char *module_dir;

/* attemp to load a server module with MODULE_PATH */
extern struct server_module *module_open(const char *module_path);

/* close a server module and deallocate the module object */
extern void module_close(struct server_module *module);

/*** symbols defined in server.c ***/
/* run the server on LOCAL_ADDR and PORT */
extern void server_run(struct in_addr local_addr, uint16_t port);


#endif /* SERVER_H */
