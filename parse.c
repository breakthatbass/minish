#include "parse.h"


// read_cmds: get commands from stdin
char *read_cmds(void)
{
    char *line = NULL;
    size_t buflen;
    getline(&line, &buflen, stdin);
    return line;
}
