#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;


const int base = 1000 * 1000 * 1000;
const int lbase = 9;


void largeAddition(vector<int>& a, vector<int>& b, vector<int>& sum);
vector<int> fibonacciCount(int nNumberOfDigits);
string outputLargeInt( vector<int>& n );


int main (int argc, char *argv[])
{

	fibonacciCount(11);
	
	return 0;
}


void largeAddition(vector<int>& a, vector<int>& b, vector<int>& sum)
{
	if (!sum.empty())
	{
		sum.clear();
	}
	if (b.size() > a.size())
	{
		while(a.size() < b.size())
		{
			a.push_back(0);
		}
	}
	else
	{
		while(b.size() < a.size())
		{
			b.push_back(0);
		}
	}
	int numAdditions = 0;
	int carry = 0;
	while (numAdditions < a.size())
	{
		long current = a[numAdditions] + b[numAdditions] + carry;
		if(current >= base)
		{
			carry = 1;
			current = current - base;
		}
		else
		{
			carry = 0;
		}
		sum.push_back(current);
		numAdditions++;
	}
	if(carry)
	{
		sum.push_back(carry);
	}
//	cout << outputLargeInt(a) << " + " << outputLargeInt ( b ) << " = " << outputLargeInt ( sum ) << endl;;	
}



vector<int> fibonacciCount(int nNumberOfDigits) //nNumberOfDigits has to be positive
{

	string szfibonacciNum = "";
	int digitCount = 0;
	int nFibNum = 2;
	vector<int> n1, n2, n;
	
	n1.push_back(1);
	n2.push_back(1);
	cout << "1: 1 (1)" << endl;
	cout << "2: 1 (1)" << endl;
	
	do
	{
		largeAddition( n1, n2, n );
		nFibNum++;
		szfibonacciNum.clear();
		szfibonacciNum = outputLargeInt( n );
		digitCount = szfibonacciNum.length();
		n1 = n2;
		n2 = n;
		n.clear();
		cout << nFibNum << ": " << szfibonacciNum << " (" << digitCount << ")" << endl;
	} while(digitCount < nNumberOfDigits);

}


string outputLargeInt(vector<int>& n )
{	
	ostringstream out;
	vector<int>::iterator iter = n.end();
	out << *--iter;
	while( iter != n.begin() )
	{
		out << setw(lbase)  <<  setfill('0')  << *--iter;
	}
	return out.str();
}