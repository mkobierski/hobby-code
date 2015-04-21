#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

ifstream* openFile()
{
	ifstream* pFileStream = 0;
	for(;;)
	{
		// open the file specified by the user
		char fileName[80] = "g.txt";
//		cout << "Enter the name of a file with integers" <<
//		endl;
//		cin >> fileName;
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

int main (int argc, char *argv[])
{
	// get a file stream
	ifstream* pFileStream = openFile();
	char buffer[256];
	
	// read number of lines
	int lineCount = 0;
	for ( ; !pFileStream->eof(); )
	{
		// read a value
		pFileStream->getline(buffer, 256);
		lineCount++;
	}
	lineCount--; // the above reads 1 too many lines
	
	cout << "lineCount = " << lineCount << endl;
	
	pFileStream->close();
	delete pFileStream;
	pFileStream = openFile();
	
	// make grid in memory
	int** nNums = new int*[lineCount];
	for(int i = 0; i < lineCount; i++)
	{
		nNums[i] = new int[i + 2]; //allow extra space for null terminator
	}
	
	// read into grid
	cout << "nNums: " << endl;
	for(int i = 0 ; !pFileStream->eof(); i++)
	{
		char szLine[512] = {0};
		pFileStream->getline(szLine, 512);
		
		if(!pFileStream->eof())
		{
//			cout << "szLine is: " << szLine << endl;
			stringstream ss;
			ss << szLine;
			int j;
			for(j = 0; j <= i; j++)
			{
				ss >> nNums[i][j];
				cout << nNums[i][j] << " ";
			}
			nNums[i][j] = -1;
			cout << nNums[i][j] << endl;
		}
		
		
		
		//stop if the file read failed (probably because
		//we ran upon something that’s not an int or
		//because we found a new line with nothing after it)
		
		if(pFileStream->fail())
		{
			
			break;
		}
	}
	
	int** nSums = new int*[lineCount];
	for(int i = 0; i < lineCount; i++)
	{
		nSums[i] = new int[i + 2]; //allow extra space for null terminator
	}
	
	// initialize nSums
	nSums[0][0] = nNums[0][0];
	nSums[0][1] = -1;
	
	// build nSums
	for (int i = 1; i < lineCount; i++)
	{
		for(int j = 0; j <= i; j++)
		{
			// left edge
			if(j == 0)
			{
				nSums[i][j] = nSums[i-1][j] + nNums[i][j];
			}
			// right edge
			else if(j == i)
			{
				nSums[i][j] = nSums[i-1][j-1] + nNums[i][j];
				nSums[i][j+1] = -1;
			}
			else
			{
				// left side parent larger
				if(nSums[i-1][j-1] > nSums[i-1][j])
				{
					nSums[i][j] = nSums[i-1][j-1] + nNums[i][j];
				}
				else
				{
					nSums[i][j] = nSums[i-1][j] + nNums[i][j];
				}
			}
		}
	}
	
	// print nSums
	cout << "nSums: " << endl;
	for (int i=0; i < lineCount; i++)
	{
		for(int j = 0; j <= i + 1; j++)
		{
			cout << nSums[i][j] << " ";
		}
		cout << endl;
	}
	
	int nLargestSum = 0;
	for(int i = lineCount - 1, j = 0; nSums[i][j] != -1; j++)
	{
		if(nSums[i][j] > nLargestSum)
		{
			nLargestSum = nSums[i][j];
		}
	}
	cout << "The largest sum is: " << nLargestSum << endl;
	
	return 0;
}

