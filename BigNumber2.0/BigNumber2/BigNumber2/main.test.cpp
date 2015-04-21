#include <cstdio>
#include <iostream>

#include "BigNumber2/Public.hpp"

Boolean test1()
{
	BigMath::BigNumber nb1, nb2;
	nb1 = "13.1234";
	nb2 = "2.2";
	BigMath::BigNumber sum;
	sum = nb1 + nb2;
	BigMath::BigNumber nb3;
	nb3 = "123";
	BigMath::BigNumber nb4("576");
	BigMath::BigNumber sum2 = nb3 + "2";
	BigMath::BigNumber sum3 = BigMath::BigNumber("4") + "296.2";

	BigMath::BigNumber copy1(sum3);

	std::cout << nb1.getAsString().data() << " is my string" << std::endl;
	std::cout << nb2.getAsString().data() << " is my string" << std::endl;
	std::cout << sum.getAsString().data() << " is my string" << std::endl;

	std::cout << nb3.getAsString().data() << " is my string" << std::endl;
	std::cout << nb4.getAsString().data() << " is my string" << std::endl;
	std::cout << sum2.getAsString().data() << " is my string" << std::endl; 

	std::cout << copy1.getAsString().data() << " is my string" << std::endl;


	getchar();
			
	return true;
}

Boolean test2()
{
	using namespace BigMath;
	BigNumber one(".22");
	BigNumber two(".221");

	assert( one <= two );
	return true;
}

int main (int argc, char *argv[])
{
	test1();
	return 0;
}

