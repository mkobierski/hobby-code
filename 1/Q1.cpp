#include "Q1.hpp"

#include <stdio.h>

namespace Q1 {

namespace Method1 {

int solve(int limit) {
    int i = 1;
    int sum = 0;
	for (i = 1; i < limit; i++) {
		if(i % 3 == 0 || i % 5 == 0) {
			sum += i;
		}
	}
	return sum;
}

int solveAndPrint() {
	int sum = solve(1000);
	printf("Q1: The sum is %i\n", sum);
	return sum;
}

}

namespace Method2{

int solveAndPrint() {
	int sum = Solve<1000>::Result;
	printf("Q1: The sum is %i\n", sum);
	return sum;
}

} // namespace Method2

int solveAndPrint() {
	return Method2::solveAndPrint();
}

}