#include "Verify.hpp"

#include "Q8.hpp"

int main () {
	check(Q8::solve<4>("files/seq.txt") == 5832);
	return 0;
}