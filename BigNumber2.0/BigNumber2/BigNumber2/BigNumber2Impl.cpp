
namespace BigMath
{
    std::string const getAsString( BigNumberImpl const & bn )
    {
    	return bn.getAsString();
    }

    BigNumberImpl::BigNumberImpl()
    : count( 1 )
    , handle( null )
    , attributes( 0 )
    , numBlocks( 0 )
    {
    	clear();
    }
    
    BigNumberImpl::~BigNumberImpl()
    {
        Memory::freeRange( handle );
    }
    
    std::string const BigNumberImpl::getAsString() const 
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
    
    Byte * BigNumberImpl::getBegin()
    {
    	return handle;
    }
    Byte const * BigNumberImpl::getBegin() const
    {
    	return const_cast< Byte const * >( handle );
    }
    Byte * BigNumberImpl::getEnd()
    {
    	return handle + count;
    }
    Byte const * BigNumberImpl::getEnd() const
    {
    	return const_cast< Byte const * >( handle + count );
    }
    Byte const * BigNumberImpl::getEndLimit() const
    {
    	return const_cast< Byte const * >( handle + ( numBlocks * BLOCK_SIZE ) );
    }
    
    Natural const BigNumberImpl::getCount() const
    {
    	return count;
	}
	
	BigNumberImpl & BigNumberImpl::operator=( BigNumberImpl & other )
	{
		if( &other == this )
		{
			return *this;
		}

	}
	BigNumberImpl & BigNumberImpl::operator=( long long other )
	{
		set( other );
	 	return *this;
	}
	BigNumberImpl & BigNumberImpl::operator=( std::string other )
	{
		set( other.data() );
		return *this;
	}
	BigNumberImpl & BigNumberImpl::operator=( char * other )
	{
		set( other );
		return *this;
	}
	
	void BigNumberImpl::set( char const * other )
	{
		clear();

		if (*other == '-')
		{
			setNegative();
			++other;
		}
		for( ; *other == '0' ; ++other );
		count = 0;
		Byte * digit = getBegin();
		while (*other && digit != getEndLimit())
		{
			char value = *other - '0';
			if (digit == getBegin())
			{
				// Keep negative intact
				*digit |= (~Mask::NEGATIVE & value);
			}
			else
			{
				*digit = value;
			}
			++digit;
			++other;
			++count;
		}
		if( !count )
		{
			// other is 0
			++count;
			unsetNegative();
		}
		if (!isValid())
		{
			clear();
		}
	}
	void BigNumberImpl::set( long long other )
	{
		clear();
		Memory::zeroRange(getBegin(), numBlocks * BLOCK_SIZE);
		if (other < 0)
		{
			setNegative();
			other *= -1;
		}
		count = 0;
		long long mask = 1;
		long long quotient = 1;
		for (;;)
		{
			quotient = other / mask;
			if (quotient == 0)
			{
				mask /= 10;
				break;
			}
			mask *= 10;
			++count;
		}
		if( !count )
		{
			// other is 0
			++count;
		}
		Byte * digit = getBegin();
		while (mask && digit != getEnd())
		{
			char value = static_cast< char >(other / mask);
			if (digit == getBegin())
			{
				// Keep negative intact
				*digit |= (~Mask::NEGATIVE & value);
			}
			else
			{
				*digit = value;
			}
			other -= *digit * mask;
			mask /= 10;
			++digit;
		}
		if (!isValid())
		{
			clear();
		}
	}

	void BigNumberImpl::setNegative()
	{
		attributes |= Mask::NEGATIVE;
	}
	void BigNumberImpl::unsetNegative()
	{
		attributes &= ~Mask::NEGATIVE;
	}
	void BigNumberImpl::reverseNegative()
	{
		attributes ^= Mask::NEGATIVE;
	}
	bool BigNumberImpl::isNegative() const
	{
		return attributes & Mask::NEGATIVE ? true : false ;
	}
	bool BigNumberImpl::isZero() const
	{
		return ( count == 1 && !*handle ) ? true : false ;
	}
	bool BigNumberImpl::isValid()
	{
		bool valid = true;
		for( Byte const * it = getBegin() ; it != getEnd() ; ++it )
		{
			if( !( *it >= 0 && *it <= 9 ) )
			{
				valid = false;
				break;
			}
		}
		return valid;
	}
	
	void BigNumberImpl::clear()
	{
		if( handle )
		{
			Memory::freeRange( handle );
			handle = null;
		}
		attributes = 0;
		count = 1;
		numBlocks = 1;
		handle = reinterpret_cast< Byte * >( Memory::allocate( BLOCK_SIZE ) );
		Memory::zeroRange( handle , BLOCK_SIZE );
	}
}
