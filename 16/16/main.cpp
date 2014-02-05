#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <cstring>
#include <sstream>



using namespace std;

int main (int argc, char *argv[])
{
	double d = pow(2,1000);


	char sz[400] = {0};
	stringstream s;
	s.precision(302); //2^1000 has 32 digits
	s << d;
	s >> sz;
	
	cout << "2^1000 = " << endl;
	cout << sz << endl << endl;
	
	int sum = 0;
	char* psz = sz;
	for (int i = 0; *(sz+i) ; psz++, i++)
	{
//		cout << i << ": " << sum << " + " << *psz << " = ";

		char num[2] = {*psz, 0};
		sum += atoi(num);
		
//		cout << sum << endl;
	}
	
	cout << "Sum: " << sum;
	
	return 0;
}

