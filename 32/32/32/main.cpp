#include <iostream>
#include <cstdio>
#include <cstdlib>

// Choose 2000 as maximum for loops, a higher number isn't needed
#define MULTIPLIER_MAX 2000

using namespace std;

class PandigitalTester
{
	protected:
		PandigitalTester(PandigitalTester& pt){}
		void stringArrayToInt(int* nNum, char* szNum)
		{
			for(int i = 0; szNum[i]; i++)
			{
				nNum[i] = szNum[i] - '0';
			}
		}
		void intArrayToString(char* szNum, int* nNum, int nNumLen)
		{
			int i = 0;
			for(; i < nNumLen; i++)
			{
				szNum[i] = nNum[i] + '0';
			}
			// Null terminate string
			szNum[i] = 0;
		}
		long intArrayToLong(int* nNum, int nNumLen)
		{
			char szNum[30];
			intArrayToString(szNum, nNum, nNumLen);
			return atol(szNum);
		}
		
	public:
		PandigitalTester(long nMultiplier = 0, long nMultiplicand = 0)
		{
			this->nMultiplier = nMultiplier;
			this->nMultiplicand = nMultiplicand;
			nProduct = nMultiplier * nMultiplicand;
			identityIsPandigital = isPandigitalIdentity();
		}
		void init(long nMultiplier = 0, long nMultiplicand = 0)
		{
			this->nMultiplier = nMultiplier;
			this->nMultiplicand = nMultiplicand;
			nProduct = nMultiplier * nMultiplicand;
			identityIsPandigital = isPandigitalIdentity();
		}
		bool isPandigitalIdentity()
		{
			char szMultiplier[30];
			char szMultiplicand[30];
			char szProduct[30];
			int nMultiplierNum[30] = {0};
			int nMultiplicandNum[30] = {0};
			int nProductNum[30] = {0};
			int nIdentityNum[90] = {0};
			int nMultiplierLen = sprintf(szMultiplier, "%li", nMultiplier);
			int nMultiplicandLen = sprintf(szMultiplicand, "%li", nMultiplicand);
			int nProductLen = sprintf(szProduct, "%li", nProduct);
			stringArrayToInt(nMultiplierNum, szMultiplier);
			stringArrayToInt(nMultiplicandNum, szMultiplicand);
			stringArrayToInt(nProductNum, szProduct);
			
			// Join identity to check its global pandigital property
			int nIdentityLen = nMultiplierLen + nMultiplicandLen + nProductLen;
			for(int i = 0; i < nIdentityLen; i++)
			{
				if(i < nMultiplierLen)
				{
					// cout << 
					nIdentityNum[i] = nMultiplierNum[i];
				}
				else if(i >= nMultiplierLen && i < nMultiplierLen + nMultiplicandLen)
				{
					nIdentityNum[i] = nMultiplicandNum[i-nMultiplierLen];
				}
				else if(i >= nMultiplierLen + nMultiplicandLen && i < nMultiplierLen + nMultiplicandLen + nProductLen)
				{
					nIdentityNum[i] = nProductNum[i-nMultiplierLen-nMultiplicandLen];
				}
				else
				{
					cout << "Broken.";
				}
			}
			if(isPandigital(intArrayToLong(nIdentityNum, nIdentityLen), 9))
			{
				return true;
			}
			return false;
		}
		bool isPandigital(long nNumToTest, int nPandigitalNum)
		{
			char szNum[30];
			int nNum[30] = {0};
			int nNumFlags[30] = {0};
			int nNumLen = sprintf(szNum, "%li", nNumToTest);
			if(nNumLen > 9)
			{
				return false;
			}
			// Write our number into an int array string
			stringArrayToInt(nNum, szNum);
			for(int i = 0; i < nNumLen; i++)
			{
				if(nNumFlags[nNum[i]] == 1)
				{
					return false;
				}
				nNumFlags[nNum[i]] = 1;
			}
			// Check that all numbers 1 through nPandigitalNum were present
			for(int i = 1; i < nPandigitalNum + 1; i++)
			{
				if(nNumFlags[i] != 1)
				{
					return false;
				}
			}
			return true;
		}
		void out()
		{
			cout << "Multiplier:   " << nMultiplier << endl;
			cout << "Multiplicand: " << nMultiplicand << endl;
			cout << "Product:      " << nProduct << endl;
			cout << "The identity is pandigital: " << identityIsPandigital << endl;
		}
		
		long nMultiplier;
		long nMultiplicand;
		long nProduct;
		bool identityIsPandigital;
};


int main (int argc, char *argv[])
{
	// Use numberMap to track which numbers we have added already.
	// This implementation is a waste of memory, but is easy to use.
	char *numberMap = new char[999999999];
	for(int i = 0; i < 999999999; i++)
	{
		numberMap[i] = 0;
	}
	long nRunningSum = 0;
	for(long i = 1; i < MULTIPLIER_MAX; i++)
	{
		for(long j = 1; j < MULTIPLIER_MAX; j++)
		{
			double di = i/double(1.0);
			double dj = j/double(1.0);
			if(di*dj <= 999999999.0)
			{
				PandigitalTester *p = new PandigitalTester;
				p->init(i, j);
				if(p->identityIsPandigital)
				{
					if(numberMap[p->nProduct] == 0)
					// We know this product is new, add it
					{
						p->out();
						cout << "Adding " << p->nProduct;
						cout << " to sum " << nRunningSum;
						cout << endl;
						nRunningSum += p->nProduct;
						numberMap[p->nProduct] = 1;
					}
				}
				delete p;
			}
		}
	}
	delete [] numberMap;
	cout << "The sum is " << nRunningSum;
	
	return 0;
}