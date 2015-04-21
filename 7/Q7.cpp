#include "Prime/PrimeSeive.hpp"

#include "Q7.hpp"

#include <stdio.h>

namespace Q7 {

int solve(int n) {
    int count = 0;
    if(n > 2) {
        ++count;
    }
    int i = 1;
    while(count < n) {
        i += 2;
        if(isPrime(i)) {
            ++count;
        }
    }
    return i;
}

int solveAndPrint() {
    const int n = 10001;
    int nthPrime = solve(n);
    printf("Q7: Prime number no %d is %d", n, nthPrime);
    return nthPrime;
}

}
