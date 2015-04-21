#include "Prime/PrimeSeive.hpp"
#include "LowestCommonMultiple.hpp"

#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

namespace LCM {

int compute(VectT const & factors) {
    return tableMethod(factors);
}

/*
 * Finds the lowest common multiple of factors using the following
 * algorithm.
 *
 *  X = (x1, x2, ..., xn), n > 1
 *  X(m) = (x1(m), x2(m), ..., xn(m)), X(1) = X
 *
 *  xk(m+1) = xk(m), k ≠ k0
 *  xk0(m+1) = xk0(m) + xk0(1).
 */
int incrementMethod(VectT const & factors) {
    if(factors.size() == 0) {
        return 0;
    }
    if(factors.size() == 1) {
        return factors[0];
    }
    assert(*std::min_element(factors.begin(), factors.end()) > 0);

    VectT steps = factors;

    VIter theMin = std::min_element(steps.begin(), steps.end());
    VIter theMax = std::max_element(steps.begin(), steps.end());
    while(*theMin != *theMax) {
        VSizeT index = theMin - steps.begin();

        assert(index < factors.size());
        assert(*theMin < std::numeric_limits<int>::max() - factors[index]);
        *theMin += factors[index];

        theMin = std::min_element(steps.begin(), steps.end());
        theMax = std::max_element(steps.begin(), steps.end());
    }
    return steps[0];
}

/*
 * Returns the LCM of given factors using a table to compute
 *
 * Example table:
 *   +-- factors
 *   v
 *   x   2   2   3   7 <-- product is LCM
 *   4   2   1   1   1
 *   7   7   7   7   1
 *   12  6   3   1   1
 *   21  21  21  7   1
 *   42  21  21  7   1
 */
int tableMethod(VectT factors) {
    const int numPrimesAvail = 65000;
    PrimeSeive<numPrimesAvail> ps;

    VIter theMax = std::max_element(factors.begin(), factors.end());
    assert(*theMax < numPrimesAvail);

    VectT lowestFactors;
    int currentPrime = 2;

    while(*theMax > 1) {
        bool foundMult = evenlyDivideEach(currentPrime, &factors);
        if(foundMult) {
            lowestFactors.push_back(currentPrime);
        } else {
            currentPrime = ps.next(currentPrime);
        }
        theMax = std::max_element(factors.begin(), factors.end());
    }

    int product = 1;
    for(VIter it = lowestFactors.begin(); it != lowestFactors.end(); ++it) {
        assert( product < std::numeric_limits<int>::max() / *it);
        product *= *it;
    }
    return product;
}

bool evenlyDivideEach(int divisor, VectT * nums) {
    bool found = false;
    for(VIter it = nums->begin(); it != nums->end(); ++it) {
        if(*it % divisor == 0) {
            *it /= divisor;
            found = true;
        }
    }
    return found;
}

}