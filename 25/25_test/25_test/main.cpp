#include <iostream>
using namespace std;

int main (int argc, char *argv[])
{
	int n1, n2, n;
	n1 = n2 = n = 0;
	
	n1 = 1;
	n2 = 1;
	
	int i = 3;
	while( i < 48)
	{
		n = n1 + n2;
		n1 = n2;
		n2 = n;
		cout << i << ": " << n << endl;
		i++;

	}
	
//	cout << n1 << " " << n2 << " " << n << endl;
	 
	
	return 0;
}

