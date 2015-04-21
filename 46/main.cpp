#include <cassert>
#include <cmath>

#include <iostream>

#include "Prime/PrimeSeive.hpp"

struct Seive {
    enum {
        size = 65000
        };
    };

template<typename T>
bool hasGolbach(unsigned num, T & seive) {
    // Check primes below num, each time adding squares
    // until we reach num.
    unsigned i = 2;
    while(i < num) {
        unsigned sum = 0;
        for(unsigned sq = 1; ; ++sq) {
            sum = i + (2*sq*sq);
            if(sum == num) {
                return true;
                }
            if(sum > num) {
                break;
                }
            }

        while(i < num && !seive->check(++i)) {
            // Advance i
            }
        }
    return false;
    }

unsigned lowestNonGolbachOddComposite() {
    // Returns 0 if not found
    std::auto_ptr<PrimeSeive<Seive::size>> pSeive(new PrimeSeive<Seive::size>);

    unsigned i = 9;
    for (unsigned i = 9; i < Seive::size; i += 2) {
        if (pSeive->check(i) == false && !hasGolbach(i, pSeive)) {
            // Golbach wasn't right!
            return i;
            }
        }

    return 0;
    }

int main() {
    unsigned lowest = lowestNonGolbachOddComposite();
    if(lowest > 0) {
        std::cout << "The lowest odd composite disproving Golbach is "
                  << lowest << std::endl;
        }
    return 0;
}
