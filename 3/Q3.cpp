#include <stdio.h>

#include "GlobalDefines.hpp"

#include "Q3.hpp"
#include "Prime/PrimeSeive.hpp"

namespace Q3 {

long long solve(long long num) {
	long long factor = num / 2;
    long long lowFactor = 1;
	for (long long i = 2; i < factor; ++i, factor = num / i) {
        // factor may have been truncated, verify it is really a factor
		if( num % factor == 0  && isPrime(factor) ) {
			return i;
		}
        if(num % i == 0 && isPrime(i)) {
            lowFactor = i;
        }
	}
	return lowFactor;
}

long long solveAndPrint() {
	const long long num = 600851475143;
	long long largestPrimeFactor = solve(num);
	printf("Q3: The largest prime factor of %" LL_FMT_STR "d is "
        "%" LL_FMT_STR "d", num, largestPrimeFactor);
	return largestPrimeFactor;
}

}