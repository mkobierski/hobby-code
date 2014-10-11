#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "Types.hpp"
#include "BigNumber2.hpp"

void * Memory::allocate( Natural bytes )
{
	return malloc( bytes );
}
void * Memory::zeroRange( void * handle , Natural bytes )
{
	if( handle )
	{
		memset( handle , 0 , bytes );
	}
	return handle;
}
void Memory::freeRange( void * handle )
{
	free( handle );
}

namespace BigMath
{
    std::string const getAsString( BigNumber const & nb )
    {
    	return nb.getAsString();
    }

    BigNumber::BigNumber()
    : count( 0 )
    , handle( null )
    , negative( false )
    , numBlocks( 0 )
    {
    	clear();
    }
    
    BigNumber::~BigNumber()
    {
        Memory::freeRange( handle );
    }
    
    std::string const BigNumber::getAsString() const 
    {
    	std::string out;
    	if( isNegative() )
    	{
    		out.push_back('-');
    	}
    	for( Byte const * it = getBegin() ; it != getEnd() ; ++it )
    	{
    		out.push_back( *it + '0' );
    	}
    	return out;
    }
    
    Byte * BigNumber::getBegin()
    {
    	return handle;
    }
    Byte const * BigNumber::getBegin() const
    {
    	return const_cast< Byte const * >( handle );
    }
    Byte * BigNumber::getEnd()
    {
    	return handle + count;
    }
    Byte const * BigNumber::getEnd() const
    {
    	return const_cast< Byte const * >( handle + count );
    }
    Byte const * BigNumber::getEndLimit() const
    {
    	return const_cast< Byte const * >( handle + ( numBlocks * BLOCK_SIZE ) );
    }
    
    Natural const BigNumber::getCount() const
    {
    	return count;
	}
	
	BigNumber & BigNumber::operator=( long long other )
	{
		clear();
		Memory::zeroRange( getBegin() , numBlocks * BLOCK_SIZE );
	 	if( other < 0 )
	 	{
	 		setNegative();
	 		other *= -1;
	 	}
	 	long long mask = 1;
	 	long long quotient = 1;
	 	for(;;)
	 	{
	 		quotient = other / mask;
	 		if( quotient == 0 )
	 		{
	 			mask /= 10;
	 			break;
	 		}
	 		mask *= 10; 
	 		++count;
	 	}
	 	
	 	Byte * digit = getBegin();
	 	while( mask && digit != getEnd() )
	 	{
	 		char value = other / mask;
	 		if( digit == getBegin() )
	 		{
	 			// Keep negative intact
	 			*digit |= ( ~Mask::NEGATIVE & value );
	 		}
	 		else
	 		{
	 			*digit = value;
	 		}
	 		other -= *digit * mask;
	 		mask /= 10;
	 		++digit;
	 	}
	 	if( !isValid() )
	 	{
	 		clear();
	 	}
	 	return *this;
	}
	BigNumber & BigNumber::operator=( std::string other )
	{
		return *this = other.data();
	}
	
	BigNumber & BigNumber::operator=( char * other )
	{
		clear();
		
		if( *other == '-' )
		{
			setNegative();
			++other;
		}
		
		Byte * digit = getBegin();
		while( *other && digit != getEndLimit() )
		{
			char value = *other - '0';
			if( digit == getBegin() )
	 		{
	 			// Keep negative intact
	 			*digit |= ( ~Mask::NEGATIVE & value );
	 		}
	 		else
	 		{
	 			*digit = value;
	 		}
			++digit;
			++other;
			++count;
		}
		if( !isValid() )
		{
			clear();
		}
		return *this;
	}
	
	void BigNumber::setNegative()
	{
		*handle | Mask::NEGATIVE;
	}
	void BigNumber::unsetNegative()
	{
		*handle & ~Mask::NEGATIVE;
	}
	void BigNumber::reverseNegative()
	{
		*handle ^ Mask::NEGATIVE;
	}
	bool BigNumber::isNegative() const
	{
		return *handle & Mask::NEGATIVE;
	}
	bool BigNumber::isEmpty() const
	{
		return !count ? true : false ;
	}
	bool BigNumber::isValid()
	{
		bool valid = true;
		bool didUnsetNegative = false;
		if( isNegative() )
		{
			unsetNegative();
			didUnsetNegative = true;
		}
		for( Byte const * it = getBegin() ; it != getEnd() ; ++it )
		{
			if( !( *it >= 0 && *it <= 9 ) )
			{
				valid = false;
				break;
			}
		}
		if( didUnsetNegative )
		{
			setNegative();
		}
		return valid;
	}
	
	void BigNumber::clear()
	{
		if( handle )
		{
			Memory::freeRange( handle );
			handle = null;
		}
		count = 0;
		numBlocks = 1;
		handle = reinterpret_cast< Byte * >( Memory::allocate( BLOCK_SIZE ) );
		Memory::zeroRange( handle , BLOCK_SIZE );
	}
}
