#include <iostream>

#include <algorithm>
#include <vector>

#include "Q41.hpp"

namespace MyTypes {
    typedef std::vector<unsigned char> VecT;
    typedef VecT::const_iterator CIterT;
    }

unsigned toUnsigned(MyTypes::VecT & digits) {
    unsigned val = 0;
    unsigned mult = 1;
    for(MyTypes::CIterT it = digits.end() - 1;; it -= 1, mult *= 10) {
        val += *it * mult;
        if(it == digits.begin()) {
            // Cannot decrement iter past begin()
            break;
            }
        }
    return val;
    }

int secondTry() {
    unsigned char setSize = 9;
    while(setSize > 1) {
        MyTypes::VecT digits;

        for(unsigned char i = setSize; i > 0; --i) {
            digits.push_back(i);
            }
        do {
            unsigned val = toUnsigned(digits);
            if( isPrime( val ) ) {
                // Found it!
                return val;
                }
            } while (std::prev_permutation(digits.begin(), digits.end()));
        --setSize;
        }
    return 0;
    }

int main()
{
    unsigned max = secondTry();

    if( max != 0 ) {
        std::cout << "The greatest pandigital prime is " << max << std::endl;
        }
    return 0;
}
