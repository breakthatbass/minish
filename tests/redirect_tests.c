#include "minunit/minunit.h"
#include "../src/minish.h"
#include "../src/parse.h"
#include <stdlib.h>
#include <stdio.h>


int main() 
{
	static char *args[20] = {"ls  ", "file", NULL};
    int a = redirect_right(args);
    return 0;
}