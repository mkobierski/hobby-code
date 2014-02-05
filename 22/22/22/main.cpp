#include <list>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;
list<string> names;

ifstream* openFile()
{
	ifstream* pFileStream = 0;
	for(;;)
	{
		// open the file specified by the user
		char fileName[80] = "names.txt";
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
	ifstream* pFileStream = openFile();
	char buffer[256];
	char* pbuffer = buffer;
	string szBuffer;
	// read number of lines
	for ( ; !pFileStream->eof(); )
	{
		// read a value
		pFileStream->getline(buffer, 256, ',');
		
		szBuffer = pbuffer;
		size_t offset;
		
		while((offset = szBuffer.find("\"")) != -1)
		{
			szBuffer.erase(offset, 1);
		}
//		cout << szBuffer << endl;
		names.push_back(szBuffer);
		
		if(pFileStream->fail())
		{
			break;
		}
	}
	
	names.sort();
	
	list<string>::iterator iter = names.begin();
	int sumOfLetters = 0;
	int prodOfLettersAndLocation = 0;
	long runningScore = 0;
	for(int i = 1; iter != names.end() ; iter++, i++)
	{
		szBuffer = *iter;
		sumOfLetters = 0;
		for(int j = 0; szBuffer[j]; j++)
		{
			sumOfLetters += szBuffer[j] - 'A' + 1;
		}
		prodOfLettersAndLocation = i * sumOfLetters;
		runningScore += prodOfLettersAndLocation;
		
	}
	
	cout << "runningScore: " << runningScore << endl;
	
	return 0;
}

