

// StreamInput - simple input from a file using fstream
#include <fstream>
#include <iostream>

using namespace std;

ifstream* openFile()
{
	ifstream* pFileStream = 0;
	for(;;)
	{
		// open the file specified by the user
		char fileName[80];
		cout << "Enter the name of a file with integers" <<
		endl;
		cin >> fileName;
		//open file for reading; don’t create the file
		//if it isn’t there
		pFileStream = new ifstream(fileName);
		if (pFileStream->good())
		{
			break;
		}
		cerr << "Couldn’t open " << fileName << endl;
		delete pFileStream;
	}
	return pFileStream;
}

int main(int nNumberofArgs, char* pszArgs[])
{

	// get a file stream
	ifstream* pFileStream = openFile();
	// stop when no more data in file
	int nValue[20][20] = {0};

	for (int i = 0 , j = 0; !pFileStream->eof(); )
	{
		// read a value
		(*pFileStream) >> nValue[i][j];
		
		//stop if the file read failed (probably because
		//we ran upon something that’s not an int or
		//because we found a new line with nothing after it)
		
		if(pFileStream->fail())
		{
			
			break;
		}
		// output the value just read

		cout.width(3);
		cout << nValue [i][j];
		i++;
		if(i == 20)
		{
			i = 0;
			j++;
			cout << endl;
		}
	}
	
	long maxProduct = 0;
	long product = 0;
	int maxI = 0, maxJ = 0;
	int orientation = -1;

	for(int i=0,j=0; j <= 19; )
	{
		product = nValue [i][j] * nValue[i+1][j] * nValue [i+2][j] * nValue [i+3][j];
		if (product > maxProduct)
		{
			maxProduct = product;
			maxI = i;
			maxJ = j;
			orientation = 0;
		}
			
		i++;
		if(i > 16)
		{
			i = 0;
			j++;
		}
	}
	
	for(int i=0,j=0; j <= 16; )
	{
		product = nValue [i][j] * nValue[i][j+1] * nValue [i][j+2] * nValue [i][j+3];
		if (product > maxProduct)
		{
			maxProduct = product;
			maxI = i;
			maxJ = j;
			orientation = 1;
		}
		
		i++;
		if(i > 19)
		{
			i = 0;
			j++;
		}
	}
	
	for(int i=0,j=0; j <= 16; )
	{
		product = nValue [i][j] * nValue[i+1][j+1] * nValue [i+2][j+2] * nValue [i+3][j+3];
		if (product > maxProduct)
		{
			maxProduct = product;
			maxI = i;
			maxJ = j;
			orientation = 2;
		}
		
		i++;
		if(i > 16)
		{
			i = 0;
			j++;
		}
	}
	
	for(int i=3,j=0; j <= 16; )
	{
		product = nValue [i][j] * nValue[i-1][j+1] * nValue [i-2][j+2] * nValue [i-3][j+3];
		if (product > maxProduct)
		{
			maxProduct = product;
			maxI = i;
			maxJ = j;
			orientation = 3;
		}
		
		i++;
		if(i > 19)
		{
			i = 3;
			j++;
		}
	}
	
	cout << endl << "maxProduct[i][j] is:" << maxProduct 
		 << " at [" << maxI << "][" 
		 << maxJ << "]" << " orientation " << orientation 
		 << endl;
	
	return 0;
}