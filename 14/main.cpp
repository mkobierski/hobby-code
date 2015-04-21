
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <iostream>

using namespace std;

class Collatz
{
	public:
		Collatz(int n = 0)
		{
			nInitNum = n;
			nChainLen = 1;
			long nC = nInitNum;
			cout << nC << " ";
			while(nC != 1)
			{
				if(nC % 2) //odd
				{ 
					nC = nC*3 + 1;
				}
				else //even
				{
					nC = nC / 2;
				}
				
	//			cout << nC << " ";
				nChainLen++;
			}
			cout << endl;
				
		}
	
		long getnChainLen()
		{
			return nChainLen;
		}
		
		int getnInitNum()
		{
			return nInitNum;
		}
		
	protected:
		long nInitNum;
		int nChainLen;
};


int main (int argc, char *argv[])
{
	int i = 0;
	Collatz* pCol;
	Collatz* plCol;
	
	plCol = new Collatz(2);
	
	do
	{
		pCol = new Collatz(++i);
		if(pCol->getnChainLen() > plCol->getnChainLen())
		{
			plCol = pCol;
		}
		
	
	} while(i < 1000000);
	
	cout << endl;
	cout << "The number " << plCol->getnInitNum() << " has a chain with " 
		 << plCol->getnChainLen() << " numbers." << endl;
	
	return 0;
}
