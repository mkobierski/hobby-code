#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "GeometricNumbers.hpp"

#include "Q42.hpp"


bool isTriangleWord(std::string const & word)
	{
	unsigned sum = 0;
	std::string::const_iterator it;
	for(it = word.begin(); it != word.end(); ++it)
		{
		sum += *it - 'A' + 1;
		}
	if(GeometricNumbers<GNTypes::Triangle>::exists(sum))
		{
		std::cout << std::setw(5) << std::left << sum;
		return true;
		}
	return false;
	}

unsigned countTriangleWords(std::string const & fname)
	{
	std::ifstream fs(fname.data());
	if(!fs.is_open())
		{
		std::cout << "Could not open file " << fname << std::endl;
		return -1;
		}
	unsigned count = 0;
	std::string word;
	std::getline(fs, word, ',');

	while(fs.good())
		{
		// Erase '"'
		word.erase(word.begin());
		word.erase(--word.end());

		if(isTriangleWord(word))
			{
			std::cout << word << std::endl;
			++count;
			}
		std::getline(fs, word, ',');
		}
	return count;
	}