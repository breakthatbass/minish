#include "parse.h"


// read_cmds: get commands from stdin
char *read_cmds(void)
{
    static char line[BUF];
    fgets(line, BUF, stdin);
    return line;
}

char *trim(char *str)
{
  char *end;
  /*
  size_t length;

  length = strlen(str);
  if (str[length-1] && str[0])
	  // no white spaces
	  return str;
*/
  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  if (*end != ' ') return str;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

// split: take a string and break it up into an array of strings based on delim
char **split(char *s, const char *delim)
{
    char **split_s;
    char *token;
    size_t length;
    int i;

    length = strlen(s);

    split_s = calloc(length*2, sizeof(char*));
    if (split_s == NULL) {
        fprintf(stderr, "split: could not allocate memory\n");
        exit(EXIT_FAILURE);
    }

    i = 0;
    token = strtok(s, delim);
    while (token != NULL) {
		split_s[i] = trim(token);
        token = strtok(NULL, delim);
        i++;
    }
	if (i > 0)split_s[i] = NULL;
    return split_s;
}

// len: get the length of an array of strings
int len(char **a)
{
	int count = 0;
	while (*a) {
		a++;
		count++;
	}
	a-=count;
	return count;
}

