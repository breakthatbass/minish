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
	 //char line[100] = {0};
	 char *line;
	 char **tokens;
	 int n;
 
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
 
        line = read_cmds();

		if (strstr(line, "|")) {

			// PIPE
			tokens = split(line, "|");
			if (tokens != NULL) {
				n = pipe_exec(tokens);
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

			tokens = split(line, " \t\r\n");
			if (*tokens != NULL) {
				n = shell_exec(tokens);
			}
		}
		free(tokens);
	}
    return 0;
}
