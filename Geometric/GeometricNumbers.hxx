#include <iomanip>
#include <iostream>
#include <set>

template<> inline
unsigned long GeometricNumbers<GNTypes::Triangle>::compute(unsigned long index)
	{
	return 0.5*index*(index + 1);
	}

template<> inline
unsigned long GeometricNumbers<GNTypes::Pentagon>::compute(unsigned long index)
	{
	return 0.5*index*(3*index - 1);
	}

template<> inline
unsigned long GeometricNumbers<GNTypes::Hexagon>::compute(unsigned long index)
	{
	return index*(2*index - 1);
	}

template<typename NumType>
void GeometricNumbers<NumType>::print(unsigned long num)
	{
	extendNums(num);
	std::set<unsigned long>::iterator it;
	for(it = nums.begin(); it != nums.end(); ++it)
		{
		std::cout << *it << ' ';
		}
	std::cout << std::endl;
	}

template<typename NumType>
void GeometricNumbers<NumType>::tidy()
	{
	if(nums.size() == 0)
		{
		nums.insert(1);
		}
	}

template<typename NumType>
unsigned long GeometricNumbers<NumType>::lastNum()
	{
	tidy();
	return *(--nums.end());
	}

template<typename NumType>
void GeometricNumbers<NumType>::extendNums(unsigned long threshold)
	{
	while(lastNum() < threshold)
		{
		unsigned long next = nums.size() + 1;
		nums.insert(compute(next));
		}
	}

template<typename NumType>
bool GeometricNumbers<NumType>::exists(unsigned long num)
	{
	if(num > lastNum())
		{
		extendNums(num);
		}
	if(nums.find(num) == nums.end())
		{
		return false;
		}
	return true;
	}