#include <iostream>
#include <cstdio>
using namespace std;

#include "BigNumber.h"

int main (int argc, char *argv[])
{
	BigMath::BigNumber a;
	cout << "\n";
	bool isTruncatablePrime;
	unsigned int count = 0;
	BigMath::BigNumber sum(0);
	for( int i = 2; count < 11 ; i++ )
	{
		a.setV( i );
		isTruncatablePrime = a.isTruncatablePrime();
		
		if( isTruncatablePrime )
		{
			cout << a.print() << endl;
			sum.add( a.print() );
			++count;
			// cout << "True\n";
		}
		else
		{
			// cout << "False\n";
		}
	}

	cout << sum.print() << " is the sum" << endl;

	getchar();
	
	return 0;
}

