#include "builtins.h"


void minish_cd(char **args)
{
    int rc = chdir(args[1]);
    if (rc != 0) {
        errmsg("cd");
    }
}


void minish_exit(char **args)
{
    free(args);

    // clear the screen on exit
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

	exit(EXIT_SUCCESS);
	// if we make it here then there are more processess
	exit(EXIT_SUCCESS);
}

void errmsg(const char *msg)
{
    char shell[15] = "minish -> ";
    char error_message[25] = "command not found -> ";
    write(STDERR_FILENO, shell, strlen(shell));
    write(STDERR_FILENO, error_message, strlen(error_message));
    write(STDERR_FILENO, msg, strlen(msg));
    write(STDERR_FILENO, "\n", 1);
}

