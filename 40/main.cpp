#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main (int argc, char *argv[])
{
	string d;
	int i = 0;
	for(int i = 1; i < 1*9 + 2*90 + 3*900 + 4*9000 + 5*90000 + 85187; i++)
	{
		char tempNum[10];
		sprintf(tempNum,"%d",i);
		d += tempNum;
	}
	cout << d << endl;
	
	int answer = (d[1-1] - '0') * (d[10-1]- '0') 	* (d[100-1]- '0') * (d[1000-1]- '0') * (d[10000-1]- '0') * (d[100000-1]- '0') * (d[1000000-1]- '0') ;
	
	cout << "Numbers: " << d[0] << ", "
		 << d[9] << ", " 
		 << d[99] << ", "
		 << d[999] << ", "
		 << d[9999] << ", "
		 << d[99999] << ", "
		 << d[999999] << endl;
	
	cout << "Answer = " << answer << endl;
	
	return 0;
}

