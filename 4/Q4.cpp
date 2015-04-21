#include "Palindrome.h"

#include "Q4Private.hpp"

#include <stdio.h>
#include <assert.h>

namespace Q4 {

int solve(int numDigits) {
    int lowerLim = pow(10, numDigits - 1) - 1;
    int upperLim = pow(10, numDigits) - 1;

	int a = upperLim;
    int b = upperLim;
    int product = 0;
    int largest = 0;
	while(a > lowerLim) {
		if(b == lowerLim) {
			a--;
			b = upperLim;
		}
        product = a * b;
		if (isPalindrome(product) && (product) > largest) {
            largest = product;
        }
		b--;
	}
	return largest;
}

int solveAndPrint() {
    int largest = solve(3);
    printf("Q4: The largest palindrome from two 3-digit numbers is %d",
           largest);
    return largest;
}

int pow(int base, int ex) {
    assert(ex >= 0);
    if(ex < 0) {
        return 0;
    }
    if(ex == 0) {
        return 1;
    }
    if(ex == 1) {
        return base;
    }
    return base * pow(base, ex - 1);
}

}