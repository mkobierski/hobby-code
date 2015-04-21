#include <iostream>

#include "GeometricNumbers.hpp"

#include "Q42.hpp"

void printUsage(int argc, char const * const argv[])
	{
	std::cout << "Usage: " << argv[0] << " path/to/words.txt" << std::endl;
	}

int main(int const argc, char const * const argv[])
	{
	if(argc != 2)
		{
		printUsage(argc, argv);
		return 1;
		}

	std::cout << "Triangle numbers..." << std::endl;
	GeometricNumbers<GNTypes::Triangle>::print(200);

	unsigned count = countTriangleWords(argv[1]);
	if(count == static_cast<unsigned>(-1))
		{
		return 1;
		}
	std::cout << "There are " << count << " triangle words.";
	return 0;
	}