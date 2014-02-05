

// StreamInput - simple input from a file using fstream
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

ifstream* openFile()
{
	ifstream* pFileStream = 0;
	for(;;)
	{
		// open the file specified by the user
		char fileName[80];
	/*	cout << "Enter the name of a file with integers" <<
		endl;
		cin >> fileName; */
		strcpy (fileName, "n.txt");
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
	double dValue[101] = {0};

	double drSum = 0;

	for (int i = 0; !pFileStream->eof(); i++)
	{
		// read a value
		(*pFileStream) >> dValue[i];
		
		//stop if the file read failed (probably because
		//we ran upon something that’s not an int or
		//because we found a new line with nothing after it)
		
		if(pFileStream->fail())
		{
			
			break;
		}
		
		drSum += dValue [i];
		// output the value just read
		cout.precision(15);
		cout << dValue [i] << endl;

	}
	
	cout.precision(15);
	cout << "Sum: " << drSum << endl;
	
/*	for (int i = 0; dValue[i]; i++)
	{
		cout << dValue[i] << endl;
	} */
	return 0;
}