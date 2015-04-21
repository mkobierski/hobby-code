#include <iostream>
#include <vector>

#include "43.hpp"

void findPandigitalSum()
{
    unsigned long long sum = 0;
    
    std::vector< unsigned long long > permutations;
    std::string pandigitalConfigStr = "0123456789";
    permute(10, pandigitalConfigStr, permutations);
    for( std::vector< unsigned long long>::iterator it = permutations.begin(); it != permutations.end(); ++it)
    {
        // Some of the permutations will implicitly start with zero,
        // offseting the required substring indexes by -1
        unsigned i = 0;
        if( *it < 1000000000 )
        {
            i = 1;
        }
        if( subTriple( 8 - i, *it ) % 17 ||
            subTriple( 7 - i, *it ) % 13 ||
            subTriple( 6 - i, *it ) % 11 ||
            subTriple( 5 - i, *it ) % 7  ||
            subTriple( 4 - i, *it ) % 5  ||
            subTriple( 3 - i, *it ) % 3  ||
            subTriple( 2 - i, *it ) % 2 )
        {
            continue;
        }
        std::cout << sum << std::endl;
        std::cout << "+" << *it << std::endl;
        std::cout << "-------------" << std::endl;
        sum += *it;
    }
    std::cout << sum << std::endl;
}

int main()
{
    findPandigitalSum();   
    return 0;
}
