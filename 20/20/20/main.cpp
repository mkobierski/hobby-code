#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

const int base = 1000 * 1000 * 1000; // base value, should be the power of 10
const int lbase = 9; // lg(base)

void output_biginteger(vector<int>& a, stringstream& s)
{
	s << a.back();
	for (int i = (int)a.size() - 2; i >= 0; --i)
	{
		s << setw(lbase) << setfill('0') << a[i];
	}
}

void multiply_biginteger_by_integer(vector<int>& a, int b) {
	int carry = 0;
	for (int i = 0; i < (int)a.size(); ++i)
	{
		long long cur = (long long)a[i] * b + carry;
		carry = cur / base;
		a[i] = cur % base;
	}
	if (carry > 0)
	{
		a.push_back(carry);
	}
}

int main() 
{
	int n = 100; // input your n here
	vector<int> current(1, n);

	for (int i = n - 1; i >= 1; --i) 
	{
		multiply_biginteger_by_integer(current, i);
	}
	
	stringstream s;
	output_biginteger(current,s);
	
	string szNum;
	s >> szNum;
	cout << "szNum :\n" << szNum << endl << endl;
	int sum = 0;
	for (int i = 0; szNum[i]; i++)
	{
	
		sum += szNum[i] - '0';
	}
	
	cout << "The sum of the numbers is " << sum << endl ;
	
	return 0;
}




//double Factorial(int i)
//{
//	if(i == 1)
//	{
//		return (double)1.0;
//	}
//	else
//	{
//		double d = (double)i;
//		d=d*Factorial(i-1);
//		return d;
//	}
//}
//
//
//int main (int argc, char *argv[])
//{
//	char szf[159] = {0};
//	stringstream s;
//	s.precision(158);
//	s << Factorial(100) << endl;
//	s >> szf;
//	cout << szf << endl;
//	int sum = 0;
//	for (int i = 0; szf[i]; i++)
//	{
//		cout << "sum: " << sum << endl;
//		sum += szf[i] - '0';
//	}
//	
//	cout << "Sum of digits: " << sum << endl;
//	return 0;
//}

