#include <iostream>
#include <cmath>
#include <list>
using namespace std;

bool d(int n);

int main (int argc, char *argv[])
{
	
	long long sum = 0;
	int array[28125] = {0};
	for(int i = 0; i < 28125; i++)
	{
		array[i] = i;
	}
	for (int i = 2; i < 28125; i++)
	{
		int j;
		for(j = 1; j <= i / 2 && array[i]; j++)
		{
			int k = i - j;
			if(d(k) && d(j))
			{
				array[i] = 0;
			}
		}
		
		if (i % 100 == 0)
		{
			cout << "i: " << i << endl;
		}
	}
	
	for(int i = 0; i < 28125; i++)
	{
		sum+= array[i];
	}
	
	cout << "The sum is: " << sum << endl;
	
	return 0;
}

bool d(int n)
{
	int sum = 0;
	if (n > 2)
	{
//		list<int> l;
		for (int i = 1; i <= sqrt(n); i++)
		{	
			if( i == 1 )
			{	
//				l.push_back(i);
				sum += i;
			}
			else if(n % i == 0)
			{	
//				l.push_back(i);
				sum += i;
				if(i != sqrt(n))
				{
					sum += n / i;
//					l.push_back(n / i);
				}
			}
		}
//		l.sort();
//		list<int>::iterator iter = l.begin();
		
//		while (iter != l.end())
//		{
//			cout << *iter << ", ";
//			iter++;
//		}
//		cout << "are proper factors of " << n << endl;
		
	}
	else if (n == 2)
	{
		sum = 1;
	}
	
	if(sum > n) { return true; }
	else { return false; }
}