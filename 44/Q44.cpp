#include <iomanip>
#include <iostream>
#include <set>

#include "GeometricNumbers.hpp"

#include "Q44.hpp"

namespace {
	void printPentagonalDifference(unsigned index1, unsigned index2)
		{
		std::cout << GeometricNumbers<GNTypes::Pentagon>::compute(index2)
				  << " - "
				  << GeometricNumbers<GNTypes::Pentagon>::compute(index1)
				  << " = "
				  << differenceOfPentagonal(index1, index2)
				  << std::endl;
		}

	void printPentagonalSum(unsigned index1, unsigned index2)
		{
		std::cout << GeometricNumbers<GNTypes::Pentagon>::compute(index2)
				  << " + "
				  << GeometricNumbers<GNTypes::Pentagon>::compute(index1)
				  << " = "
				  << sumOfPentagonal(index1, index2)
				  << std::endl;
	}
}
unsigned differenceOfPentagonal(unsigned index1, unsigned index2)
	{
	return GeometricNumbers<GNTypes::Pentagon>::compute(index2)
		   - GeometricNumbers<GNTypes::Pentagon>::compute(index1);
	}

bool differenceIsPentagonal(unsigned index1, unsigned index2)
	{
	return GeometricNumbers<GNTypes::Pentagon>::exists(differenceOfPentagonal(index1, index2));
	}

unsigned sumOfPentagonal(unsigned index1, unsigned index2)
	{
	return GeometricNumbers<GNTypes::Pentagon>::compute(index1)
		   + GeometricNumbers<GNTypes::Pentagon>::compute(index2);
	}

bool sumIsPentagonal(unsigned index1, unsigned index2)
	{
	return GeometricNumbers<GNTypes::Pentagon>::exists(sumOfPentagonal(index1, index2));
	}

unsigned solve44()
	{
	unsigned lowIndex = 1;
	unsigned highIndex = 2;
	for(;;)
		{
		if(sumIsPentagonal(lowIndex, highIndex) &&
		    differenceIsPentagonal(lowIndex, highIndex))
			{
			break;
			}
		++lowIndex;
		if(lowIndex == highIndex)
			{
			lowIndex = 1;
			++highIndex;
			}
		}
	printPentagonalSum(lowIndex, highIndex);
	printPentagonalDifference(lowIndex, highIndex);

	unsigned p1 = GeometricNumbers<GNTypes::Pentagon>::compute(lowIndex);
	unsigned p2 = GeometricNumbers<GNTypes::Pentagon>::compute(highIndex);
	// std::cout << p1 << " " << p2 << std::endl;
	return p2 - p1;
	}
