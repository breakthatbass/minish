#include "minunit/minunit.h"
#include "../src/minish.h"
#include "../src/parse.h"
#include <stdlib.h>
#include <stdio.h>

static char *args1[20] = {"ls ", " wc"};
static char *args2[20] = {"ls -a", "wc -l"};

static int a = 0;
static int b = 0;

void test_setup(void)
{   
    a = pipe_exec(args1);
    b = pipe_exec(args2);
}

void test_teardown(void)
{
    // nothing
}

MU_TEST(test_check) 
{
    mu_check(a == EXIT_SUCCESS);
    mu_check(b == EXIT_SUCCESS);
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