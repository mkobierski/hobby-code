
#include <cmath>
#include <iostream>

#include "q39.h"

namespace ProjectEuler39
{
	RightTriangle::RightTriangle( unsigned _a, unsigned _b )
	: a(_a)
	, b(_b)
	, c(0)
	{
		double tmp = sqrt(a*a + b*b);
		c = static_cast< unsigned >( round( tmp ) );
		if( !(c - tmp < tol) ) 
		{
			// Resulting right triangle does not have integral sides
			a = 0;
			b = 0;
			c = 0;
		}
	}

	bool const RightTriangle::isValid() const
	{
		if( a > 0 && b > 0 && c > 0 && c*c == (a*a) + (b*b) )
		{
			return true;
		}
		return false;
	}

	void RightTriangle::print() const 
	{
		std::cout << "("  << a 
				  << ", " << b
			  	  << ", " << c
			  	  << ") = " << perim()
				  << std::endl;
	}
}

int main()
{
	unsigned trianglesPerPerim[ProjectEuler39::MAX_PERIM + 1] = {0};

	ProjectEuler39::RightTriangle ok( 3, 4 );
	bool OK = ok.isValid();

	for( unsigned a = 1 ; a < ( ProjectEuler39::MAX_PERIM / 3 ) - 1; ++a ) 
	{
		for( unsigned b = a ; ;  ++b )
		{
			ProjectEuler39::RightTriangle t( a, b );
			if( t.perim() > ProjectEuler39::MAX_PERIM )
			{
				break;
			}
			if( t.isValid() && t.perim() == 840 )
			{
				++trianglesPerPerim[ t.perim() ];
				t.print();
			}
		}
	}
	unsigned maxCount = 0;
	unsigned maxPerim = 0;
	for( unsigned i = 0 ; i < ProjectEuler39::MAX_PERIM ; ++i )
	{
		if( trianglesPerPerim[i] > maxCount )
		{
			maxPerim = i;
			maxCount = trianglesPerPerim[i];
		}
	}
	std::cout << "Maximized perim: " << maxPerim
			  << " with " << maxCount << " values." << std::endl;
	return 0;
}