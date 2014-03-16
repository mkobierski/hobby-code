#include <iostream>
#include <cstdio>

#define RANGE_TO_TEST 1000000

using namespace std;

int intToBinary(char *szABinary, int n)
// Converts an integer to a c string containing its binary
// representation.  Leading zeroes are not appended.  The return
// value is the length of the binary string returned.  The binary
// string is stored in szABinary, passed by reference.
{
	bool firstOneAssigned = false;
	int nLenN = 0;
	// 0x4000 0000 checks the integer value neglecting the sign bit
	// Right-shift this filter through all bits to, adding 1 to the
	// string if the bitwise 'and' is 1, otherwise adding 0.
	// Only begin tracking when the first 1 value is found.
	for(int b = 0x40000000; b > 0; b >>= 1)
	{
		if(b & n)
		{
			*szABinary++ = '1';
			nLenN++;
			firstOneAssigned = true;
		}
		else if(firstOneAssigned)
		{
			*szABinary++ = '0';
			nLenN++;
		}
	}
	*szABinary = '\0';	
	return nLenN;
}

bool isPalindrome(char *szN, int nLenN)
// Checks a string szN of length nLenN for palindromicity
{
	bool isPalindrome = true;
	for(int i = 0, j = nLenN - 1; i < j; i++, j--)
	{
		//printf ("%i, %i\n", i, j);
		if(szN[i] != szN[j])
			isPalindrome = false;
	}
	return isPalindrome;
}

bool isDoublePalindrome(int n)
// Converts given number n to base 2, then checks both the base 10
// and base 2 palindrome property.  Returns true if both representations
// are palindromic.  Prints all numbers which satisfy this property.
{
	int nLenA = 0;
	int nLenABinary = 0;
	char *szA = new char[7];
	char *szABinary = new char[7*8];
	nLenA = sprintf(szA, "%i", n);
	nLenABinary = intToBinary(szABinary, n);
	if(isPalindrome(szA, nLenA) && isPalindrome(szABinary, nLenABinary))
	{
		cout << szA << " (" << szABinary << ")" << endl;
		return true;
	}
	return false;
}

int main (int argc, char *argv[])
{
	char *szNBinary = new char[7*8];
	long sum = 0;
	for(int i = 0; i < RANGE_TO_TEST; i++)
	{
		if(isDoublePalindrome(i))
		{
			sum += i;
		}
	}
	cout << "The sum of all numbers below " << RANGE_TO_TEST
		 << " palindromic in" << endl
		 << "base 10 and base 2:" << endl
		 << sum;
	return 0;
}

