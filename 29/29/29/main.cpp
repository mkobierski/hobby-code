#include <iostream>

#include "bignumber.h"

#define LOWBOUND 2
#define HIGHBOUND 100

using namespace std;
using namespace BigMath;

int main (int argc, char *argv[])
{
	vector< vector<int> > numberArray;
	
	BigNumber a;
	int k = 0;
	for(int i = LOWBOUND; i <= HIGHBOUND; i++)
	{
		for(int j = LOWBOUND; j <= HIGHBOUND; j++)
		{
			a.setV(i);
			a.big_pow(j);
//			cout << k << ": " << i << "^" << j
//			     << " = " << a.print() << "    ";
			numberArray.push_back(a.returnV());
			k++;
		}
//		cout << endl;
	}
	
	vector< vector<int> > _numberArray;
	
	bool numExists = false;
	for(int i = 0; i < numberArray.size(); i++)
	{
//		cout << i << ", ";
		for(int j = 0; j < _numberArray.size(); j++)
		{
			if(BigNumber::equalTo(numberArray[i], _numberArray[j]))
			{
				numExists = true;
				cout << "Found double: " << i << ", " << j << endl;
				break;
			}
		}
		if(!numExists)
		{
			_numberArray.push_back(numberArray[i]);
		}
		numExists = false;
	}
	cout << endl;
	
	cout << "Size: " << _numberArray.size() << endl;
	
//	cout << a.print() << endl;
	
	return 0;
}

