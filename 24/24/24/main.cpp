#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iomanip>
using namespace std;

long Factorial(int i);
long computeLexical(vector<int> l, int n);

int main (int argc, char *argv[])
{
	int nPermNum = -1;
	while ( nPermNum < 0 )
	{
		cout << "Enter the lexical permutation number: " << endl;
		cin >> nPermNum;
		
	}
	nPermNum--;
	
	int nArray[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> items( nArray, nArray + sizeof(nArray)/sizeof(int) );
	
	long nLexicalNumber;
	
	nLexicalNumber = computeLexical (items, nPermNum);
	cout << "The " << nPermNum + 1 << " lexical permutation of: " << endl;
	for(vector<int>::iterator i = items.begin(); i != items.end(); i++)
	{
		cout << setw(3) << *i;
	}
	cout << endl << "is: " << endl;
	cout << setw(items.size()) << setfill('0') << nLexicalNumber << endl;
	
	return 0;
}

long computeLexical(vector<int> l, int n)
{
	int nInitialSize = l.size();
	int nFactBase = nInitialSize - 1;
//	cout << "nFactBase: " << nFactBase << endl;
	string szLexicalNumber = "";
	
	
	int nFact, nDiv;
	while(nFactBase >= 0)
	{
		nFact = Factorial(nFactBase);
		nDiv = n / nFact;
//		cout << "n/nFact: " << (n / nFact) << endl;
//		cout << "l[(n/nFact)]: " << l[(n / nFact)] << endl;
		szLexicalNumber.push_back( l[nDiv] + '0');
		l.erase(l.begin()+nDiv);
//		cout << "n1: " << n << endl;
		n = n - nDiv * nFact;
//		cout << "n2: " << n << endl;
		nFactBase--;
//		cout << szLexicalNumber << endl;
	
	}
	
	return atol(szLexicalNumber.c_str());
}

long Factorial(int i)
{
	if(i == 0) return 1;
	else return i*Factorial(i-1);
}