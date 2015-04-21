#include <iostream>
#include <limits>
#include <bitset>

#ifdef HAVE_BOOST
#   include "boost/static_assert.hpp"
#endif

template<size_t sz>
PrimeSeive<sz>::PrimeSeive()
: seiveReady(false)
{
#ifdef HAVE_BOOST
	BOOST_STATIC_ASSERT_MSG(sz >= 2,
		"PrimeSeive must be instantiated using a size greater than 1");
#endif
}

template<size_t sz>
bool PrimeSeive<sz>::initSeive(SizeT num) {
	if(num >= sz)
	{
		std::cout << "Seive is not configured for numbers above "
				  << sz - 1 << std::endl;
		return false;
	}

#	ifndef HAVE_BOOST
	if(sz < 2) {
		std::cout << "PrimeSeive only configured for numbers above 1 ";
		return false;
	}
#	endif

	seive.set();
	seive[0] = false;
	seive[1] = false;
	return true;
}

template<size_t sz>
void PrimeSeive<sz>::compute(SizeT maxLimit) {
	seiveReady = false;

	if(!initSeive(maxLimit))
	{
		return;
	}
	SizeT half = (sz + 1) / 2;
	for (SizeT i = 2; i < half; ++i) {
		if(seive[i] == true) {
			// Number at index is prime
			for (SizeT iMultiple = 2 * i; iMultiple < sz; iMultiple += i) {
				seive[iMultiple] = false;
			}
		}
	}
	seiveReady = true;
}

template<size_t sz>
void PrimeSeive<sz>::verifySeive(SizeT val) {
	if(!seiveReady || val >= sz) {
		compute(val);
	}
}

template<size_t sz>
bool PrimeSeive<sz>::check(SizeT val) {
	verifySeive(val);
	if(seiveReady) {
		return seive[val];
	}
	return false;
}

template<size_t sz>
typename PrimeSeive<sz>::SizeT PrimeSeive<sz>::next(SizeT val) {
	verifySeive(++val);
	if(seiveReady) {
		for(; val < sz && !seive[val]; ++val) {}
		return val;
	}
	return 0;
}