#ifndef __BUILTINS_H__
#define __BUILTINS_H__

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void minish_cd(char **args);
void minish_exit(char **args);
void errmsg(const char *msg);

// this struct and builtins array prevent a big if/else chain
// if a lot of builtin functions are added
struct builtin {
    char *name;
    void (*f)(char **args);
};


#endif

