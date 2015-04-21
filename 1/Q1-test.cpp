#include "Q1.hpp"
#include "Verify.hpp"

#include <iostream>

int main() {
    check(Q1::Method1::solve(10) == 23);
    check(Q1::Method2::Solve<10>::Result == 23);
    return 0;
}