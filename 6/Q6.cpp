#include "Q6Private.hpp"

#include <stdio.h>

namespace Q6 {

// Range is inclusive of llim and ulim
long long solve(int llim, int ulim) {
	return sqOfSumRange(llim, ulim) - sumOfSqRange(llim, ulim);
}

long long solveAndPrint() {
	const int lowerLimit = 1;
	const int upperLimit = 100;
	long long diff = solve(lowerLimit, upperLimit);
	printf("Q6: The difference of sum of squares and square of sums\n"
		   "    for the numbers between %d and %d is %d",
		   lowerLimit, upperLimit, diff);
	return diff;
}

long long sumOfSqRange(int llim, int ulim) {
	long sum = 0;
	for (int i = llim; i <= ulim ; ++i) {
		sum += i * i;
	}
	return sum;
}

long long sqOfSumRange(int llim, int ulim) {
	long sum = 0;
	for (int i = llim; i <= ulim ; ++i) {
		sum += i;
	}
	return sum*sum;
}

}