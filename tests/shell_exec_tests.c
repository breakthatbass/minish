#include "minunit/minunit.h"
#include "../src/minish.h"
#include <stdlib.h>
#include <stdio.h>

static char *args1[] = {"ls", NULL};
static char *args2[] = {"ls -a", NULL};
static char *args3[] = {"sdfsd"};

static int a = 0;
static int c = 0;


void test_setup(void)
{   
    a = shell_exec(args1);
    c = shell_exec(args3);
    
    //printf("RETURN CODE: %d\n", c);
}

void test_teardown(void)
{
    
}


MU_TEST(test_check) 
{
    mu_check(a == 0);
    //mu_check(c == 1);
}

MU_TEST(test_assert_int_eq)
{
   // mu_assert_int_eq(EXIT_FAILURE, c);
}


MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_check);
    MU_RUN_TEST(test_assert_int_eq);
}


int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
