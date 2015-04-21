#include <iostream>
#include <vector>
#include <cmath>
#define UBOUND 10000
using namespace std;



int d(int n);


int main (int argc, char *argv[])
{
	
	vector<int> anum();
	int compare = 0;
	int sum = 0;
	for(int i = 2; i < UBOUND; i++)
	{
		compare = d(i);
	//	cout << "i: " << i << " compare: " << compare << " d(compare): " << d(compare) << endl;
		if(i == d(compare) && i != compare)
		{
			cout << "Amicable number: " << i << endl;
			sum += i;
		}
	}
	
//	cout << d(284) << endl;
	

	cout << "The sum of amicable numbers below " << UBOUND << " is: " << sum;
	
	return 0;
}

int d(int n)
{
	int sum = 0;
	if (n > 2)
	{
		for (int i = 1; i < n; i++)
		{
			if(n % i == 0)
			{
				sum += i;
//				cout << i << " is a divisor of " << n << endl;
			}
		}
	}
	else if (n == 2)
	{
		sum = 1;
	}
	
	return sum;
	
}