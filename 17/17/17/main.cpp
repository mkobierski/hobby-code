#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class Words
{
	public:
		static const char* szOnes[];
		static const char* szTens[];
		static const char* szHundred;
		static const char* szThousand;	
};
const char* Words::szOnes[] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
						   "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
						   "eighteen", "nineteen" };

const char* Words::szTens[] = { "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };

const char* Words::szHundred = "hundred";

const char* Words::szThousand = "thousand";

class NumberInWords
{
	public:
		NumberInWords(int n)
		{
			nNumber = n;
			nLetterCount = 0;
			stringstream szs;
			szs << n;
			szs >> szNumber;
			nNumOfDigits = szNumber.length();
			szNumberInW = "";
			
			buildString();
			countString();
			printString();
			
		}
		
		~NumberInWords()
		{
		}
		
		void newNum(int n)
		{
			nNumber = n;
			nLetterCount = 0;
			stringstream szs;
			szs << n;
			szs >> szNumber;
			nNumOfDigits = szNumber.length();
			szNumberInW = "";
			
			buildString();
			countString();
			printString();
		}
		
		void buildString()
		{
			switch(szNumber.length())
			{
				case 0:
					cout << "String length less than 0" << endl;
					break;
				case 4:
					szNumberInW.append(Words::szOnes[ szNumber[szNumber.length() - 4] - '0' ]);
					szNumberInW = szNumberInW + " " + Words::szThousand + " ";
				case 3:
					if(szNumber[szNumber.length() - 3] != '0')
					{
						szNumberInW.append(Words::szOnes[ szNumber[szNumber.length() - 3] - '0' ]);
						szNumberInW = szNumberInW + " " + Words::szHundred + " ";
					}
				case 2:
					if (szNumber.length() > 2 && (szNumber[szNumber.length() - 2] != '0' || szNumber[szNumber.length() - 1] != '0'))
					{
						szNumberInW += "and ";
					}
					if (szNumber[szNumber.length() - 2] - '0' > 1)
					{
						szNumberInW.append(Words::szTens[ szNumber[szNumber.length() - 2] - '0' ]);
						szNumberInW += " ";
					}
					else if (szNumber[szNumber.length() - 2] - '0' == 1)
					{
						szNumberInW.append(Words::szOnes[ (szNumber[szNumber.length() - 2] - '0')*10 + (szNumber[szNumber.length() - 1] - '0') ]);
						szNumberInW += " ";
					}
					
				case 1:
					if (szNumber.length() > 1 )
					{
						if(szNumber[szNumber.length() - 2] - '0' == 1)
						{
							szNumberInW += "";
						}
						else
						{
							szNumberInW.append(Words::szOnes[ szNumber[szNumber.length() - 1] - '0' ]);
						}
					}
					else
					{
						szNumberInW.append(Words::szOnes[ szNumber[szNumber.length() - 1] - '0' ]);
					}
					break;
					
				default:
					cout << "Default: Shouldn't end up here." << endl;
			}
			
			
		}
		
		int countString()
		{
			if(szNumberInW.length() < 0)
			{
				cout << "String length < 0" << endl;
				return 0;
			}
			else
			{
				nLetterCount = 0;
				for(int i = 0; i < szNumberInW.length(); i++)
				{
					if(szNumberInW[i] >= 'a' && szNumberInW[i] <= 'z')
					{
						nLetterCount++;
					}
				}
			}
		}
		
		void printString()
		{
			if(szNumberInW.length())
			{
				cout << nNumber << " is written " << szNumberInW
					 << " (" << nLetterCount << ")" << endl;
			}
			else
			{
				cout << "Nothing in string" << endl;
			}
		}
		
		int getNumLetters()
		{
			return nLetterCount;
		}
			
	protected:
		int nNumber;
		int nNumOfDigits;
		int nLetterCount;
		string szNumber;
		string szNumberInW;
};

int main (int argc, char *argv[])
{

	NumberInWords niw(0);
	unsigned int nRunningCount = 0; 

	for (int i = 1; i <= 1000; i++)
	{
		niw.newNum(i);
		nRunningCount += niw.getNumLetters();
	}
	
	cout << "The total number of characters is: " << nRunningCount << endl;


	return 0;
}

