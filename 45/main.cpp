#include <iostream>

#include "GeometricNumbers.hpp"

int main()
	{
	std::cout << "Triangle numbers..." << std::endl;
	GeometricNumbers<GNTypes::Triangle>::print(200);

	std::cout << "Pentagonal numbers..." << std::endl;
	GeometricNumbers<GNTypes::Pentagon>::print(200);
	
	std::cout << "Hexagonal numbers..." << std::endl;
	GeometricNumbers<GNTypes::Hexagon>::print(200);

	std::cout << std::endl << std::endl;

	unsigned result = 0;
	for(unsigned n = 144; ; ++n)
	// H(143) == T(285) == P(165), what is the next num like this?
		{	
		result = GeometricNumbers<GNTypes::Hexagon>::compute(n);
		if(GeometricNumbers<GNTypes::Triangle>::exists(result) &&
		   GeometricNumbers<GNTypes::Pentagon>::exists(result))
			{
			break;		
			}
		}

	std::cout << "The number " << result 
			  << " is Triangular, Pentagonal, and Hexagonal.";

	return 0;
	}