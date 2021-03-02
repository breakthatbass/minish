#ifndef __MINISH_H__
#define __MINISH_H__

// shell_exec: execute a command in a child process
int shell_exec(char **args);

// make_proc: determine if a process goes to stdout or takes in data from stdin
void make_proc(int in, int out, char **cmd);

// pipe_exec: loop through each command, connecting each through a pipe
void pipe_exec(char *line);

#endif

