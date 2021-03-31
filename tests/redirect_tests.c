//#include "minunit/minunit.h"
#include "../src/minish.h"
#include "../src/parse.h"
#include "../src/redirect.c"
#include <stdlib.h>
#include <stdio.h>


int main() 
{
	static char *args[20] = {"ls  ", "file", NULL};
    int a = redirect_out(args);
	if (a == 0) printf("passed!\n");
    return 0;
}
