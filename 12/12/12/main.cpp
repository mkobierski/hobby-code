
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <iostream>

using namespace std;

class triNum
{
	public:
		triNum(int n = 0)
		{
			for(int i = 1; i <= n; i++)
			{
				nTriNumber += i;
			}
			
			if(nTriNumber == 1)
			{
				nNumFac = 1;
			}
			else
			{
				for(int i = 1; i < sqrt(nTriNumber); i++)
				{
					if(nTriNumber % i == 0)
					{
						nNumFac += 2;
					}
				}
			}
		}
	
		long getnTriNumber()
		{
			return nTriNumber;
		}
		
		int getnNumFac()
		{
			return nNumFac;
		}
		
	protected:
		long nTriNumber;
		int nNumFac;
};


int main (int argc, char *argv[])
{
	int i = 0;
	triNum* ptNum;
	do
	{
		ptNum = new triNum(++i);
		
	
	} while(ptNum->getnNumFac() <= 500);
	
	cout << "The " << i << "th triangle number is " 
		 << ptNum->getnTriNumber() << " with " 
		 << ptNum->getnNumFac() << " factors." << endl;
	
	return 0;
}

