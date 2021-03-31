#include <unistd.h>
#include "parse.h"
#include "minish.h"
#include "redirect.h"

#define RED_B "\033[31;1m"
#define YEL_B "\033[33;1m"
#define PURPLE_B "\033[34;1m"
#define END "\033[0m"

#define PATH_MAX 45

int main()
{
	char *line;
	char **tokens;
	int n, pstat;
	pid_t pid;
 
    while (1) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd))) {
            // print cwd
            printf("%s%s%s\n", YEL_B, cwd, END);
            printf("%sminish%s %s->%s ", RED_B, END, PURPLE_B, END);
        } else {
            // if there's an issue with getcwd() just print the prompt
            printf("%sminish%s %s->%s ", RED_B, END, PURPLE_B, END);
        }

		// eat up zombie processes
		while ((pid = waitpid(WAIT_ANY, &pstat, WNOHANG)) > 0);
 
		// just make sure input is empty if it happens to not be
		if (line != NULL) {
			(void)memset(line, '\0', strlen(line));
			//free(line);
		}

        line = read_cmds();
		if (line == NULL) return EXIT_FAILURE;

		// for now we can't both pipes and redirection together...maybe someday
		if (strstr(line, "|") && (strstr(line, ">") || strstr(line, "<"))) {
			fprintf(stderr, "error: minish cannot use pipes and redirection in the same command...but maybe someday\n");
			continue;
		}

		if (strstr(line, "|")) {

			// PIPE
			tokens = split(line, "|");
			if (tokens != NULL) {
				n = pipe_exec(tokens);
				if (n == 1) exit(1);
			}

		} else if (strstr(line, ">")) {

			// REDIRECTION OUT
			tokens = split(line, ">");
			if (tokens != NULL) {
				printf("WE'RE GOING OUT\n");
				redirect_out(tokens);
			}

		} else if (strstr(line, "<")) {

			// REDIRECTION IN
			tokens = split(line, "<");
			if (tokens != NULL) {
				printf("WE'RE GOING IN\n");
				redirect_in(tokens);
			}

		} else {
			// REGULAR COMMAND
			tokens = split(line, " \t\r\n");
			printf("in main: /%s/\n", *tokens);
			if (*tokens != NULL) {
				n = shell_exec(tokens);
			}
		}
		free(tokens);
	} // end of while loop
    return 0;
}
