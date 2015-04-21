
namespace BigMath
{
    BigNumericalData::BigNumericalData()
	: handle( null )
	, count( 0 )
	, numBlocks( 0 )
	{
	}
	BigNumericalData::~BigNumericalData()
	{
		reset();
	}
	BigNumericalData::BigNumericalData( BigNumericalData const & other )
	: handle( null )
	, count( other.count )
	, numBlocks( other.numBlocks )
	{
		if( other.handle )
		{
			handle = reinterpret_cast< Byte * >( Memory::allocate( numBlocks * BLOCK_SIZE ) );
			Memory::copyRange( other.handle , handle , numBlocks * BLOCK_SIZE );
		}
	}
	BigNumericalData & BigNumericalData::operator=( BigNumericalData const & other )
	{
		BigNumericalData temp( other );
		swap( temp );

		return *this;
	}
	void BigNumericalData::swap( BigNumericalData & other )
	{
		using std::swap;

		swap( handle , other.handle );
		swap( count , other.count );
		swap( numBlocks , other.numBlocks );
	}

	void BigNumericalData::init( Natural _numBlocks )
	{
		if( numBlocks == _numBlocks && handle)
		{
			Memory::zeroRange( handle , numBlocks * BLOCK_SIZE );
		}
		else
		{
			if( handle )
			{
				Memory::freeRange( handle );
				handle = null;
			}
			numBlocks = _numBlocks;
			handle = reinterpret_cast< Byte * >( Memory::allocate( numBlocks * BLOCK_SIZE ) );
			Memory::zeroRange( handle , BLOCK_SIZE );
		}
		// An initialized value has one digit equal to 0
		count = 1;
	}
	void BigNumericalData::reset()
	{
		if( handle )
		{
			Memory::freeRange( handle );
			handle = null;
		}
		count = 0;
		numBlocks = 0;
	}

	bool const BigNumericalData::isInitialized() const
	{
		return ( count && handle );
	}
	bool const BigNumericalData::isZero() const
	{
		return ( count == 1 && handle && !*handle );
	}

    Byte * BigNumericalData::getBegin()
    {
    	return handle;
    }
    Byte const * BigNumericalData::getBegin() const
    {
    	return const_cast< Byte const * >( handle );
    }
    Byte * BigNumericalData::getEnd()
    {
    	return handle + count;
    }
    Byte const * BigNumericalData::getEnd() const
    {
    	return const_cast< Byte const * >( handle + count );
    }
    Byte const * const BigNumericalData::getEndLimit() const
    {
    	return const_cast< Byte const * >( handle + ( numBlocks * BLOCK_SIZE ) );
    }

    Boolean operator==( BigNumericalData const & left , BigNumericalData const & right )
    {
    	if( left.count != right.count )
    	{
    		return false;
    	}
		auto lIt = left.getBegin();
		auto rIt = right.getBegin();
    	for( ; 
    		 lIt != left.getEnd() && rIt != right.getEnd() ; 
    		 ++lIt , ++rIt )
    	{
    		if( *lIt != *rIt )
    		{
    			return false;
    		}
    	}
    	return true;
    }
}
