#ifndef GEOMETRIC_NUMBERS__INCLUDED
#define GEOMETRIC_NUMBERS__INCLUDED

#include <set>

namespace GNTypes 
	{
	class Triangle {};
	class Pentagon {};
	class Hexagon {};
	}

template<typename NumType>
  class GeometricNumbers
	{
		GeometricNumbers();
		GeometricNumbers(GeometricNumbers const &);
		virtual ~GeometricNumbers() = 0;
		static void tidy();
		static unsigned long lastNum();
		static void extendNums(unsigned long);

		static std::set<unsigned long> nums;

	public:
		static unsigned long compute(unsigned long);
		static bool exists(unsigned long);
		static void print(unsigned long);
	};

template<typename T> std::set<unsigned long> GeometricNumbers<T>::nums;

#include "GeometricNumbers.hxx"

#endif // GEOMETRIC_NUMBERS__INCLUDED