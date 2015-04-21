#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <assert.h>

#include "Q41.hpp"

unsigned const LimitedNum::MAX_ = 1000000000;
unsigned const PandigitalTracker::MAX_DIGITS = 9;       

LimitedNum::LimitedNum( unsigned long long n )
: _num( 0 )
{
    num( n );
}

bool const LimitedNum::num( unsigned long long n )
{
    if( n < LimitedNum::MAX_ )
    {
        _num = n;
        return true;
    }
    _num = 0;
    return false;
}

PandigitalTracker::PandigitalTracker( LimitedNum n )
: _num( n.num() )
, flags( 0 )
{
    init();
}
void PandigitalTracker::init()    
{
    char szNum[MAX_DIGITS + 1];
    sprintf( szNum, "%u", _num );
    for( char const * pc = szNum; *pc; ++pc )
    {
        switch( *pc )
        {
            case '1':
                flags |= Bit::ONE;
                break;
            case '2':
                flags |= Bit::TWO;
                break;
            case '3':
                flags |= Bit::THREE;
                break;
            case '4':
                flags |= Bit::FOUR;
                break;
            case '5':
                flags |= Bit::FIVE;
                break;
            case '6':
                flags |= Bit::SIX;
                break;
            case '7':
                flags |= Bit::SEVEN;
                break;
            case '8':
                flags |= Bit::EIGHT;
                break;
            case '9':
                flags |= Bit::NINE;
                break;
            case '0':
            default:
                break;
        } 
    }
}

bool const PandigitalTracker::isPandigital() const
{ 
    unsigned checkFlags = 0;
    for( unsigned i = 0; i < numDigits( _num ); ++i )
    {
        checkFlags |= 1 << i;
    }
    return flags == checkFlags;
}

unsigned const numDigits( unsigned long long n )
{
    unsigned c = 1;
    for( unsigned i = 10; n / i; i *= 10 )
    {
        ++c;
    }
    return c;
}

bool isPrime(unsigned val) {
    // prime numbers are able to be written as 6k +/- 1
    if(val <= 3) {
        return (val >= 2);
        }
    if(val % 2 == 0 || val % 3 == 0) {
        return false;
        }
    unsigned root = static_cast<unsigned>(sqrt(val)) + 1;
    for(unsigned i = 6; i < root; i += 6) {
        if(val % (i - 1) == 0 || val % (i + 1) == 0) {
            return false;
            }
        }
    return true;
    }
