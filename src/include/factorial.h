#pragma once
int factorial(int _number) { return _number <= 1 ? _number : factorial(_number - 1) * _number; }

TEST_CASE("testing the factorial function") {
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
    INFO("The factorial function");
}