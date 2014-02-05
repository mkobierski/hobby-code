#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bignumber.h"

using namespace std;


int main()
{
	string vToCheck;
	BigMath::BigNumber a;
	bool test;
	while (true)
	{
		cout << "Enter a number to check: ";
		cin >> vToCheck;
		a.setV(vToCheck);
		test = a.isPrime();
		cout << a.print() << " is ";
		if(!test)
		{
			cout << "*NOT* ";
		}
		cout << "prime." << endl;
	}
	/*
	BigMath::BigNumber a(71);
//	cout << a.print() << endl;
	bool test = a.isPrime();
	cout << "test: " << test << endl;
//	cout << a.print() << endl;
	cout << endl << endl;*/
//	cout << a.print() << endl;
//	cout << b.print() << endl;
	return 0;
}
