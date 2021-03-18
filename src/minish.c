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


// make_proc: determine if a process goes to stdout or takes in data from stdin
void make_proc(int in, int out, char **cmd)
{
    pid_t rc;
    int status;
    rc = fork();
    if (rc < 0) {
        perror("fork");
        exit(1);
    }
    if (rc  == 0) {
        if (in != STDIN_FILENO) {
            dup2(in, STDIN_FILENO);
            close(in);
        }
        if (out != STDOUT_FILENO) {
            dup2(out, STDOUT_FILENO);
            close(out);
        }
        execvp(*cmd, cmd);
        errmsg(*cmd);
		exit(1);
    }
    waitpid(rc, &status, WUNTRACED);
    return;
}


// pipe_exec: loop through each command, connecting each through a pipe
int pipe_exec(char **args)
{
    int p = 0;
    while(*args) {
        printf("/%s/\n", *args);
        args++;
        p++;
    }
    args -= p;
    int in, status, return_val;
    int pipe_no; // keep track of no. of cmds seperated by pipes 
    int pfd[2];
    //int return_status[2]; // pipe to know
    pid_t rc;
    char **cmd; // **pipe_cmds;
    
    // split takes a string and splits into array of strings based on delimiter
    //pipe_cmds = split(line, "|");
	
	return_val = EXIT_SUCCESS;
    in = 0;
    pipe_no = 0;
    while (*args) {
        cmd = split(*args, " \t\r\n");
		if (!args[1]) {
			break;
		}

        if (pipe(pfd) < 0) {
            perror("pipe");
        }

        make_proc(in, pfd[1], cmd);
        close(pfd[1]);
        in = pfd[0];
        args++;
        pipe_no++;
    }
    // move pointer back and free
    args -= pipe_no;
    //free(args);

    rc = fork();
    if (rc < 0) {
        perror("fork");
        exit(1);
    }
    if (rc == 0) {
        if (in != 0) dup2(in, STDIN_FILENO);
        execvp(*cmd, cmd);
        errmsg(*cmd);
		return_val = EXIT_FAILURE;
        exit(1);
    }
    waitpid(rc, &status, WUNTRACED);
    return return_val;
}

