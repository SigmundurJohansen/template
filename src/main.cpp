#define DOCTEST_CONFIG_DISABLE
#include <doctest/doctest.h>
#include <iostream>
#include "include/prime_factorial.h"
#include "include/factorial.h"

bool TESTING = true;

int program();

int main(int _argc, char **_argv)
{
    int client_return_code = 0;
    int test_query = 0;

    if (TESTING)
    {
        doctest::Context context;
        context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in the name
        context.setOption("rand-seed", 374);              // if order-by is set to "rand" use this seed
        context.setOption("order-by", "file");            // sort the test cases by file and line
        // overrides
        context.setOption("no-breaks", false); // don't break in the debugger when assertions fail
        test_query = context.run();            // run queries, or run tests unless --no-run is specified
        if (context.shouldExit())              // important - query flags (and --exit) rely on the user doing this
            return test_query;                 // propagate the result of the tests

        context.clearFilters(); // removes all filters added up to this point
    }

    client_return_code = program();

    return test_query + client_return_code; // the result from doctest is propagated here as well
}

TEST_CASE("[string] testing std::string")
{
    std::string a("omg");
    CHECK(a == "omg");
}

TEST_CASE("[math] basic stuff")
{
    CHECK(6 > 5);
    CHECK(6 > 7);
}

int program()
{
    printf("Program code.\n");
    prime_factorial(317798230);
    return 0;
}