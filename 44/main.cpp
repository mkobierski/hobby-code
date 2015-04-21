#include <iostream>

#include "GeometricNumbers.hpp"

#include "Q44.hpp"

int main()
	{
	std::cout << "Pentagonal numbers..." << std::endl;
	GeometricNumbers<GNTypes::Pentagon>::print(200);
	std::cout << std::endl;

	unsigned res = solve44();
	std::cout << "\nThe minimized difference of the two pentagonal numbers\n"
			  << "satisfying Pj + Pk = Pn and Pj - Pk = Pn is:\n"
			  << res << std::endl;
	return 0;
	}