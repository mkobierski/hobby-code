#include <cstdio>
#include <iostream>

#include "BigNumber2.hpp"

using namespace std;

int main (int argc, char *argv[])
{
	BigMath::BigNumber nb;
	BigMath::BigNumber nbCopy;
	nb = "-11";
	nbCopy = nb;
	cout << nb.getAsString().data() << " is my string" << endl;
	cout << nbCopy.getAsString().data() << " is my string" << endl;

	getchar();
			
	return 0;
}

