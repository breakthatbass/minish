#include "minunit/minunit.h"
#include "../src/minish.h"
#include "../src/parse.h"
#include <stdlib.h>
#include <stdio.h>

#define MAXSTR 50

static char line2[MAXSTR] = "ls | wc\n";
static char line1[MAXSTR] = "ls -a | wc -l\n";
static char line3[MAXSTR] = "ls|wc\n";
static char line4[MAXSTR] = "ls     |	wc\t\r\n";
static char line5[MAXSTR] = "ls | wc | wc -l\n";

static char **args1;
static char **args2;
static char **args3;
static char **args4;
static char **args5;

static int a = 0;
static int b = 0;
static int c = 0;
static int d = 0;
static int e = 0;

void test_setup(void)
{   
	args1 = split(line1, "|");
	args2 = split(line2, "|");
	args3 = split(line3, "|");
	args4 = split(line4, "|");
	args5 = split(line5, "|");
    
	a = pipe_exec(args1);
    b = pipe_exec(args2);
	c = pipe_exec(args3);
	d = pipe_exec(args4);
	e = pipe_exec(args5);
}

void test_teardown(void)
{
    free(args1);
	free(args2);
	free(args3);
	free(args4);
	free(args5);
}

MU_TEST(test_check) 
{
    mu_check(a == EXIT_SUCCESS);
    mu_check(b == EXIT_SUCCESS);
    mu_check(c == EXIT_SUCCESS);
    mu_check(d == EXIT_SUCCESS);
    mu_check(e == EXIT_SUCCESS);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_check);
}

int main() 
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
