#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <iostream>
#include "include/prime_factorial.h"
#include "include/factorial.h"
#include "../test/factorial_test.h"

int main(int _argc, char **_argv)
{
    doctest::Context context;
    int res = context.run(); // run

    printf("Program code.\n");
    prime_factorial(31798230);
    return 0;
}
