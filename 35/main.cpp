#include <iostream>
#include <cstdio>

#include "bignumber.h"

#define UPPER_LIMIT 1000000

using namespace std;
using namespace BigMath;

int main (int argc, char *argv[])
{
	int numCircularPrime = 0;
	float percentComplete = 0, newPercentComplete = 0;
	char filter[UPPER_LIMIT];
	BigNumber bn;
	for (int i = 0; i < UPPER_LIMIT; i++)
	{
		filter[i] = 1;
	}
	for(int i = 2; i < UPPER_LIMIT; i++)
	{
		if(filter[i] != 0)
		{
			bn.setV(i);
			if(bn.isCircularPrime())
			{
				cout << bn.print() << " - Circular prime!" << endl;
				numCircularPrime++;
				// For efficiency, here we should mark all circulations
				// of the current number as prime in filter so they are
				// not checked a second time.  For a circular prime number
				// like 919393, we can automatically add 6 (its length) to
				// numCircularPrime.
			}
			else
			{
				// bn is not circular prime, thus all numbers derived from 
				// circulating it should be marked in filter as with a 0
			}
			// In future iterations, skip numbers which have i as a factor
			for(int j = 1; j*i < UPPER_LIMIT; j++)
			{
				filter[j*i] = 0;
			}
		}
		// Give feedback on completion percentage
		newPercentComplete = float(i)/UPPER_LIMIT;
		if(newPercentComplete-percentComplete > 0.025)
		{
			percentComplete = newPercentComplete;
			printf("Percent complete: %4f\n", percentComplete*100);
		}
	}
	cout << "There are " << numCircularPrime
		 << " circular prime numbers below "
		 << UPPER_LIMIT << endl;

	return 0;
}

