#include <iostream>
#include <sstream>
#include <string>
#define NUMFRACTIONS 1001

using namespace std;

class Fraction 
{
	public:
		Fraction(int n = 0, int d = 1)
		{
			setNumDen(n,d);
		}	 	
	 	
	 	int setNumDen(int n, int d)
	 	{
	 		if(d == 0)
			{
				cout << "Error: null denominator." << endl;
			}
			else
			{
				
				negative = false;
				if(n < 0)
				{
					nNumerator = -n;
					negative = true;
				}
				else
				{
					nNumerator = n;
				}
				
				if(d < 0)
				{
					nDenominator = -d;
					negative = !negative;
				
				}
				else
				{
					nDenominator = d;
				}
				szDecimalValue = "";
				nRepeatDecimals = 0;
			}
			return 0;
	 	}
	 	
	 	int computeDecimalValue()
		{
			szDecimalValue = "";
			int lastRemainder[nDenominator + 1];
			for(int i = 0; i < nDenominator; i++)
			{
				lastRemainder[i] = 0;
			}
			int nRemainder = nNumerator;
			int nPrevRemainder = 0;
			int nQuotient = 0;

			for(int i = 1; i < 2*nDenominator; i++)
			{
				nQuotient = nRemainder / nDenominator;
				nRemainder = nRemainder - nQuotient * nDenominator;
				if(nRemainder == 0) //found finite decimal
				{
					szDecimalValue += (char) (nQuotient + '0');
					if(i == 1)
					{
						szDecimalValue += ".0";
					}
					break;
				}
				else if(lastRemainder[nRemainder]) //found repeating decimal
				{
					szDecimalValue += (char) (nQuotient + '0');
					nRepeatDecimals = i - lastRemainder[nRemainder];

					szDecimalValue.insert(lastRemainder[nRemainder] + 1,1, '(');
					szDecimalValue += ')';

					break;
				}
				else
				{
					szDecimalValue += (char) (nQuotient + '0');
					if(i == 1)
					{
						szDecimalValue += ".";
					}
					lastRemainder[nRemainder] = i;
					nRemainder = nRemainder * 10;
				}
			}
		}
		
		int out()
		{
			cout << nNumerator << "/" << nDenominator << " = " << szDecimalValue << endl;
			return 0;
		}
	 	
	 	bool negative;
	 	int nNumerator;
	 	int nDenominator;
	 	int nRepeatDecimals;
	 	string szDecimalValue;
	 	
	 protected:
		Fraction(Fraction& f){}
		


};

int main (int argc, char *argv[])
{
	Fraction frac[NUMFRACTIONS];
	int maxRep, maxRepDen;
	maxRep = maxRepDen = 0;
	for(int i = 1; i < NUMFRACTIONS; i++)
	{
		frac[i-1].setNumDen(1,i);
		frac[i-1].computeDecimalValue();
		if(frac[i-1].nRepeatDecimals > maxRep)
		{
			maxRep = frac[i-1].nRepeatDecimals;
			maxRepDen = i;
		}
		frac[i-1].out();
	}
	
	cout << "Maximum repeated decimal (" << maxRep << ") repeats: " << endl;
	frac[maxRepDen-1].out();
	
	return 0;
}

