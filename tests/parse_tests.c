#include "minunit/minunit.h"
#include "../src/parse.h"

static char teststr1[] = "hello how are you";
static char **hello;

void test_setup(void)
{
    hello = split(teststr1, " ");
}

void test_teardown(void)
{
    free(hello);
}

MU_TEST(test_string_eq)
{
    mu_assert_string_eq(*hello, "hello");
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_string_eq);
}


int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
