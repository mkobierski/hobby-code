#include <cstdio>
#include <climits>
#include <vector>

#include "GlobalDefines.hpp"
#include "LowestCommonMultiple.hpp"

namespace Q5 {
/*
 * Returns the first number which is evenly divisible by numbers
 * 1 through 'factor'.  If solution greater than limit, return -1.
 */
long long solve(int factor) {
    std::vector<int> factors;
    for(int i = factor; i > 0; --i) {
        factors.push_back(i);
    }
    return LCM::compute(factors);
}

long long solveAndPrint() {
	const int factor = 20;
	long long num = solve(factor);
	printf("Q5: The smallest number evenly divisible by 1 through %d is "
        "%" LL_FMT_STR "d",
		   factor, num);
	return num;
}

}