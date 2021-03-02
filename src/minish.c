#include "builtins.h"
#include "parse.h"
#include "minish.h"

struct builtin builtins[] = {
    {"cd", minish_cd},
    {"exit", minish_exit}
};
// builtin_len: returns the number of items in builtins struct
size_t builtin_len() {return sizeof (builtins)/sizeof (struct builtin);}


// shell_exec: execute a command in a child process
int shell_exec(char **args)
{
    int status;
    pid_t rc;
    size_t i;
	 int pfd[2];
    size_t len = builtin_len();

    // first check if command is a builtin command
    for (i = 0; i < len; i++) {
        if (strcmp(args[0], builtins[i].name) == 0) {
            builtins[i].f(args);
            return EXIT_SUCCESS;
        }
    }
	
	 // set up pipe between child and parent
	 int failed = 0;
	 if (pipe(pfd) < 0) {
		 perror("pipe failure");
		 exit(EXIT_FAILURE);
	 }

    rc = fork();
    if (rc == 0) {
        execvp(args[0], args);
        // if we make it here, there's a problem
        errmsg(*args);
		  // now we connect the pipe
		  int n = EXIT_FAILURE;
		  close(pfd[0]);
		  write(pfd[1], &n, sizeof(n));
    } else if (rc > 1) {
        // we're in the parent and we want to wait for proc tp finish
        waitpid(rc, &status, WUNTRACED);
		  int n;
		  close(pfd[1]);
		  read(pfd[0], &n, sizeof(n));
		  failed = n;

		  return failed;

    }
	 return failed;
}
