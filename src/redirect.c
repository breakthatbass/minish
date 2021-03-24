#include "parse.h"
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

#include "redirect.h"

void redirect_in(char **tokens)
{
	int pfd[2];	// pipe
	pid_t pid1, pid2;

	// will have something like
	// {"python test.py", "file"}
	char *file = trim(tokens[1]);
	char **cmd = split(tokens[0], " ");

	// we need to file to be within an array for exec to work
	// this just produces {"cat", "file.ext", NULL};
	char **file_arr = calloc(3, sizeof(char *));
	*file_arr = calloc(strlen("cat")+1, sizeof(char));
	*(file_arr + 1) = calloc(strlen(file)+1, sizeof(char));
	*(file_arr + 2) = NULL;

	assert(*file_arr);
	assert(*(file_arr+1));

	strcpy(*file_arr, "cat");
	strcpy(*(file_arr+1), file);
	
	if (pipe(pfd) < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}


	pid1 = fork();
	if (pid1 < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid1 == 0) {
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);

		execvp(file_arr[0], file_arr);
		perror("exec");
		exit(EXIT_FAILURE);
	}

	pid2 = fork();
	if (pid2 < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid2 == 0) {
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[1]);

		execvp(cmd[0], cmd);
		perror("exec");
		exit(EXIT_FAILURE);
	}
	close(pfd[0]);
	close(pfd[1]);

	int status;
	waitpid(pid1, &status, WUNTRACED);
	waitpid(pid2, &status, WUNTRACED);

	free(*file_arr);
	free(*(file_arr+1));

	free(cmd);
	free(file_arr);
}
