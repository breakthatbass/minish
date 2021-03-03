#include "builtins.h"
#include "parse.h"
#include "minish.h"


struct builtin builtins[] = {
    {"cd", minish_cd},
    {"exit", minish_exit}
};
// builtin_len: returns the number of items in builtins struct
size_t builtin_len() {return sizeof (builtins)/sizeof (struct builtin);}



/***
 * shell_exec: execute a command in a child process
 *
 * the return value is for simple testing. otherwise we'd have
 * to test it by piping the sdout into a variable or something
 * and test that which would actually be better testing. but for
 * now, we just test success or failure.
 * */
int shell_exec(char **args)
{
    int status, return_val;
    pid_t rc;
	 int pfd[2];
    size_t len, i;

	 // by default we assume success
	 return_val = EXIT_SUCCESS;

    // first check if command is a builtin command
	 len = builtin_len();
    for (i = 0; i < len; i++) {
        if (strcmp(args[0], builtins[i].name) == 0) {
            builtins[i].f(args);
            return return_val;
        }
    }
	
	 // set up pipe between child and parent to get the return value
	 if (pipe(pfd) < 0) {
		 perror("pipe");
		 exit(EXIT_FAILURE);
	 }

    rc = fork();
	 if (rc < 0) {
		 perror("fork");
		 exit(EXIT_FAILURE);
	 } else if (rc == 0) {
        execvp(args[0], args);
        // if we make it here, there was a problem with the command
        errmsg(*args);
		  return_val = EXIT_FAILURE;

		  // let the parent process know there was a problem
		  close(pfd[0]);
		  write(pfd[1], &return_val, sizeof(return_val));
		  close(pfd[1]);
    }
	 // we're in the parent and we want to wait for proc to finish
	 waitpid(rc, &status, WUNTRACED);
	 
	 // read from the pipe, if there was a problem, we'll know
	 close(pfd[1]);
	 read(pfd[0], &return_val, sizeof(return_val));
	 close(pfd[0]);
	 //printf("RETURN VAL IN PARENT: %d\n", return_val);

	 return return_val;
}
