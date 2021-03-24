#ifndef __PARSE_H__
#define __PARSE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF 1025

// red_cmds: get commands from stdin and return it as a string
char *read_cmds(void);

// split: take a string and break it up into an array of strings based on delim
char **split(char *s, const char *delim);

// trim: trim leading and trailing whitespace on a string
char *trim(char *s);

// len: get the length of an array of strings
int len(char **a);

#endif
