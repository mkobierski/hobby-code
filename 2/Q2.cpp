#include "Q2.hpp"

#include <assert.h>
#include <stdio.h>

namespace Q2 {

// Returns the sum of even valued fibonacci numbers below limit
int solve(int limit) {
	assert(limit >= 0);
	int f1 = 1;
	int f2 = 1;
	int f3 = 2;
	int sum = 0;
	while (f3 <= limit) {
		if(f3 % 2 == 0){
			sum = sum + f3;
		}
		f1 = f2;
		f2 = f3;
		f3 = f1 + f2;
	}
	return sum;
}

int solveAndPrint() {
	const int limit = 4000000;
	int sum = solve(limit);
	printf("Q2: The sum of even fibonacci numbers below %d is %d", limit, sum);
	return sum;
}

}