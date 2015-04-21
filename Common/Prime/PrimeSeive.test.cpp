#include <cassert>
#include <limits>
#include <memory>
#include <vector>

#include "PrimeSeive.hpp"

bool test1() {
	PrimeSeive<7> ps;

	assert(ps.check(0) == false);
	assert(ps.check(1) == false);
	assert(ps.check(2) == true);
	assert(ps.check(3) == true);
	assert(ps.check(4) == false);
	assert(ps.check(5) == true);

	return true;
}

bool test2() {

	std::auto_ptr<PrimeSeive<ULONG_MAX / 2>> pSeive(new PrimeSeive<ULONG_MAX / 2>);

	assert(pSeive->check(1994967293) == false);
	//assert(ps.check(std::numeric_limits<PrimeSeive::DiffT>::max() - 33) == false);
	//assert(ps.check(std::numeric_limits<PrimeSeive::DiffT>::max() - 32) == false);
	return true;
}

int main()
{
	test1();
	test2();
	return 0;
}