#pragma once

#include <cmath>
#include <bitset>

template<size_t sz>
class PrimeSeive {
	typedef std::bitset<sz> SeiveType;

public:
	typedef size_t SizeT;

	PrimeSeive();
private:
	PrimeSeive(PrimeSeive const &);	// not defined
	PrimeSeive & operator=(PrimeSeive const &); // not defined

	bool initSeive(SizeT);
	void compute(SizeT);
	void verifySeive(SizeT);

	SeiveType seive;
	bool seiveReady;

public:
	bool check(SizeT val);
	SizeT next(SizeT val);
};
template< typename T >
bool isPrime(T val) {
	// prime numbers are able to be written as 6k +/- 1
	if(val <= 3) {
		return (val >= 2);
		}
	if(val % 2 == 0 || val % 3 == 0) {
		return false;
		}
	unsigned root = static_cast<unsigned>(sqrt(val)) + 1;
	for(unsigned i = 6; i <= root; i += 6) {
		if(val % (i - 1) == 0 || val % (i + 1) == 0) {
			return false;
			}
		}
	return true;
	}

#include "PrimeSeive.hxx"
