#include <iostream>
#include <cstdio>
using namespace std;

int factorial(int n)
{
	if (n == 0 || n == 1) return 1;
	else return n*factorial(n-1);
}

int main (int argc, char *argv[])
{

	long runningSum = 0;
	
	for(int i = 3; i < 300000; i++)
	{
		long sum = 0;
		char szInt[12] = {0};
		
		sprintf(szInt,"%d",i);
//		cout << szInt << "   ";
//		cout << factorial((int)(szInt[0] - '0')) << endl;
		for(int j = 0; szInt[j]; j++)
		{
			sum += factorial((int)szInt[j]-'0');
		}
		
//		cout << i << ": Sum = " << sum << endl;
		
		if(i == sum)
		{
			cout << i << " is equal to its factorial sum." << endl;
			runningSum += i;
		}
		
	}
	cout << "Sum of Factorial numbers: " << runningSum << endl;
	return 0;
}

