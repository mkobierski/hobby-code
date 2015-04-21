
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

#include "43.hpp"

void permute( unsigned len, std::string & inArray, std::vector< unsigned long long > & outArray )
{
    using std::swap;
    if( len == 1 )
    {
        unsigned long long toPush = 0;
        if(inArray[0] == '0')
        {
            toPush = strtoull( inArray.data() + 1, NULL, 0 );
        }
        else
        {
            toPush = strtoull( inArray.data(), NULL, 0 );
        }
        outArray.push_back( toPush );
    }
    else
    {
        for( unsigned i = 1; i <= len; ++i )
        {
            permute( len - 1, inArray, outArray );
            unsigned j = 0;
            if( len % 2 )
            {
                j = 1;
            }
            else
            {
                j = i;
            }
            swap( inArray[j - 1], inArray[len - 1] );
        }
    }
}

unsigned const subTriple( unsigned index, unsigned long long num )
{
    char buf[32];
    sprintf( buf, "%llu", num );
    return subTriple( index, buf );
}

unsigned const subTriple( unsigned index, std::string const & szNum )
{
    unsigned retVal = 0;
    if( index > 0 && index <= szNum.size() - 2 )
    {
        --index;
        retVal += ( szNum[index] - '0' ) * 100;
        retVal += ( szNum[index + 1] - '0' ) * 10;
        retVal += ( szNum[index + 2] - '0' );
    }
    else
    {
        std::cout << "Warning, index out of bounds. (index = " << index 
                  << ", num = " << szNum << ")" << std::endl;
    }
    return retVal;
}

