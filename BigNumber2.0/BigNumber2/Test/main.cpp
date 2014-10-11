#include <cstdio>
#include <iostream>

#include "BigNumber2.hpp"

using namespace std;

int main (int argc, char *argv[])
{
	BigMath::BigNumber nb;
	nb = "-1289736412098734506918234650192834512347942318";
	if( !nb.isEmpty() )
	{
		cout << nb.getAsString() << " is my string" << endl;
	}
	else
	{
		cout << "awwwwww" << endl;
	}
	getchar();
			
	return 0;
}

