namespace BigMath
{    
	std::string const getAsString( BigNumber const & bn )
    {
    	return bn.getAsString();
    }
	
    BigNumber::BigNumber()
    : attributes( 0 )
    {
    	init();
    }

    BigNumber::~BigNumber()
    {
    }

	BigNumber::BigNumber( BigNumber const & other )
	: attributes( other.attributes )
	, wholePart( other.wholePart )
	, decimalPart( other.decimalPart )
	{
	}

	void BigNumber::init()
	{
		attributes = 0;
		wholePart.init();
		if( decimalPart.isInitialized() )
		{
			decimalPart.reset();
		}
	}

	void BigNumber::swap( BigNumber & other )
	{
		using std::swap;

		swap( attributes , other.attributes );
		swap( wholePart , other.wholePart );
		swap( decimalPart , other.decimalPart );  
	}
    
    std::string const BigNumber::getAsString() const 
    {
    	std::string out;
    	if( isNegative() )
    	{
    		out.push_back('-');
    	}
    	for( Byte const * it = wholePart.getBegin() ; it != wholePart.getEnd() ; ++it )
    	{
    		out.push_back( *it + '0' );
    	}
    	if( hasDecimal() )
    	{
    		out.push_back('.');
    		for( Byte const * it = decimalPart.getBegin() ; it != decimalPart.getEnd() ; ++it )
	    	{
	    		out.push_back( *it + '0' );
	    	}
    	}
    	return out;
    }
	
	BigNumber & BigNumber::operator=( BigNumber const & other )
	{
		if( &other == this )
		{
			return *this;
		}
		BigNumber temp( other );
		swap( temp );
		return *this;
	}

	void BigNumber::set( double other )
	{
		MK::String temp( other );
		set( temp );
	}

	void BigNumber::set( long long other )
	{
		init();
		if (other < 0)
		{
			setNegative();
			other *= -1;
		}

		Natural count = 0;
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
		if( count )
		{
			// other is non-zero
			wholePart.count = count;
		}
		Byte * digit = wholePart.getBegin();
		while ( mask && digit != wholePart.getEnd() )
		{
			*digit = static_cast< Byte >( other / mask );
			other -= *digit * mask;

			++digit;
			mask /= 10;
		}
		if (!isValid())
		{
			assert(0);
		}
	}

	void BigNumber::set( MK::String const & other_str )
	{
		char const * other = other_str.get().data();
		init();

		if (*other == '-')
		{
			setNegative();
			++other;
		}

		// Discard leading zeroes
		for( ; *other == '0' ; ++other );

		Natural count = 0;
		Byte * digit = wholePart.getBegin();
		for( ; *other && digit != wholePart.getEndLimit() ; ++other )
		{
			if( *other == '.' )
			{
				setHasDecimal();
				++other;
				break;
			}

			*digit++ = *other - '0';
			++count;
		}
		if( count )
		{
			wholePart.count = count;
		}
		if( hasDecimal() )
		{
			count = 0;
			digit = decimalPart.getBegin();
			for( ; *other && digit != decimalPart.getEndLimit() ; ++other )
			{
				*digit++ = *other - '0'; 
				++count;
			}
			if( count )
			{
				decimalPart.count = count;
				// Strip trailing decimal zeroes
				for( auto it = decimalPart.getEnd() - 1 ; it != decimalPart.getBegin() ; --it )
				{
					if( *it != 0 )
					{
						break;
					}
					--decimalPart.count;
				}
			}
		}
		
		if( isZero() )
		{
			unsetNegative();
		}
		if ( !isValid() )
		{
			assert(0);
		}
	}

	void BigNumber::setNegative()
	{
		attributes |= Mask::NEGATIVE;
	}
	void BigNumber::unsetNegative()
	{
		attributes &= ~Mask::NEGATIVE;
	}
	void BigNumber::reverseNegative()
	{
		attributes ^= Mask::NEGATIVE;
	}
	void BigNumber::setHasDecimal()
	{
		decimalPart.init();
		attributes |= Mask::DECIMAL;
	}
	void BigNumber::unsetHasDecimal()
	{
		decimalPart.reset();
		attributes &= ~Mask::DECIMAL;
	}
	bool const BigNumber::isNegative() const
	{
		return attributes & Mask::NEGATIVE ? true : false ;
	}
	bool const BigNumber::isZero() const
	{
		return ( wholePart.isZero() && ( !decimalPart.isInitialized() || decimalPart.isZero() ) ) ? true : false ;
	}
	bool const BigNumber::isValid()
	{
		bool valid = true;
		for( Byte const * it = wholePart.getBegin() ; it != wholePart.getEnd() ; ++it )
		{
			if( !( *it >= 0 && *it <= 9 ) )
			{
				valid = false;
				break;
			}
		}
		if( hasDecimal() )
		{
			for( Byte const * it = decimalPart.getBegin() ; it != decimalPart.getEnd() ; ++it )
			{
				if( !( *it >= 0 && *it <= 9 ) )
				{
					valid = false;
					break;
				}
			}
		}
		return valid;
	}
	bool const BigNumber::hasDecimal() const
	{
		return attributes & Mask::DECIMAL ? true : false ;
	}

	BigNumber operator+( BigNumber const & left , BigNumber const & right )
	{
		BigNumber sum;
		Natural count = static_cast< Natural >( MK::Max( left.decimalPart.count , right.decimalPart.count ) );
		Byte carry = 0;
		if( count )
		{
			sum.setHasDecimal();
			sum.decimalPart.count = static_cast< Natural >( count );
			// FIXME: Shouldn't do this check here
			if( sum.decimalPart.getEnd() > sum.decimalPart.getEndLimit() )
			{
				assert( 0 );
			}
			--count;
			for( auto it = sum.decimalPart.getEnd() - 1 ; it >= sum.decimalPart.getBegin() ; --it , --count )
			{
				if( count < left.decimalPart.count )
				{
					*it += *( left.decimalPart.getBegin() + count );
				}
				if( count < right.decimalPart.count )
				{
					*it += *( right.decimalPart.getBegin() + count );
				}
				*it += carry;
				carry = 0;
				if( *it > 9 )
				{
					*it -= 10;
					carry = 1;
				}
			}
		}
		count = static_cast< Natural >( MK::Max( left.wholePart.count , right.wholePart.count ) );
		sum.wholePart.count = count;
		if( sum.wholePart.getEnd() > sum.wholePart.getEndLimit() )
		{
			assert( 0 );
		}
		count = 0;
		for( auto it = sum.wholePart.getEnd() - 1 ; it >= sum.wholePart.getBegin() ; --it , ++count )
		{
			if( count < left.wholePart.count )
			{
				*it += *( left.wholePart.getEnd() - count - 1 );
			}
			if( count < right.wholePart.count )
			{
				*it += *( right.wholePart.getEnd() - count - 1 );
			}
			*it += carry;
			carry = 0;
			if( *it > 9 )
			{
				*it -= 10;
				carry = 1;
			}
		}
		if( carry )
		{
			if( sum.wholePart.getEnd() < sum.wholePart.getEndLimit() )
			{
				for( auto it = sum.wholePart.getEnd() ; it > sum.wholePart.getBegin() ; --it )
				{
					*it = *( it - 1 );
				}
				*sum.wholePart.getBegin() = carry;
			}
			else
			{
				// FIXME: Get more memory
				assert( 0 );
			}
		}
		return sum;
	}

	//BigNumber operator-( BigNumber const & left , BigNumber const & right )
	//{
	//	BigNumber difference;
	//	// BigNumber left(_left); // So we can modify during borrows
	//	Natural count = static_cast< Natural >( MK::Max( left.decimalPart.count , right.decimalPart.count ) );
	//	Byte carry = 0;
	//	if( count )
	//	{
	//		sum.setHasDecimal();
	//		sum.decimalPart.count = static_cast< Natural >( count );
	//		// FIXME: Shouldn't do this check here
	//		if( sum.decimalPart.getEnd() > sum.decimalPart.getEndLimit() )
	//		{
	//			assert( 0 );
	//		}
	//		--count;
	//		for( auto it = sum.decimalPart.getEnd() - 1 ; it >= sum.decimalPart.getBegin() ; --it , --count )
	//		{
	//			if( count < left.decimalPart.count )
	//			{
	//				*it += *( left.decimalPart.getBegin() + count );
	//			}
	//			if( count < right.decimalPart.count )
	//			{
	//				*it += *( right.decimalPart.getBegin() + count );
	//			}
	//			*it += carry;
	//			carry = 0;
	//			if( *it > 9 )
	//			{
	//				*it -= 10;
	//				carry = 1;
	//			}
	//		}
	//	}


	//	return difference;
	//}

	Boolean operator==( BigNumber const & left , BigNumber const & right )
	{
		if( left.wholePart == right.wholePart && 
			left.decimalPart == right.decimalPart &&
			left.viewAttributes() == right.viewAttributes() )
		{
			return true;
		}
		return false;
	}
	Boolean operator!=( BigNumber const & left , BigNumber const & right )
	{
		return !( left == right );
	}

	Boolean operator>( BigNumber const & left , BigNumber const & right )
	{
		if( left != right && left >= right )
		{
			return true;
		}
		return false;
	}
	Boolean operator>=( BigNumber const & left , BigNumber const & right )
	{
		if( !left.isNegative() && right.isNegative() )
		{
			return true;
		}
		else if( left.isNegative() && !right.isNegative() )
		{
			return false;
		}
		if( !left.isNegative() )
		{
			if( left.wholePart.count > right.wholePart.count )
			{
				return true;
			}
			if( left.wholePart.count < right.wholePart.count )
			{
				return false;
			}
		}
		else
		{
			if( left.wholePart.count > right.wholePart.count )
			{
				return false;
			}
			if( left.wholePart.count < right.wholePart.count )
			{
				return true;
			}
		}
		{
			auto lIt = left.wholePart.getBegin();
			auto rIt = right.wholePart.getBegin(); 
			for( ; lIt != left.wholePart.getEnd() && rIt != right.wholePart.getEnd() ; ++lIt , ++rIt )
			{
				if( *lIt == *rIt )
				{
					continue;
				}
				if( !left.isNegative() )
				{
					return *lIt > *rIt ;
				}
				else
				{
					return *lIt < *rIt ;
				}
			}
		}
		if( left.hasDecimal() || right.hasDecimal() )
		{
			auto lIt = left.decimalPart.getBegin();
			auto rIt = right.decimalPart.getBegin();
			for( ; lIt != left.decimalPart.getEnd() && rIt != right.decimalPart.getEnd() ; ++lIt , ++rIt )
			{
				if( *lIt == *rIt )
				{
					continue;
				}
				if( !left.isNegative() )
				{
					return *lIt > *rIt ;
				}
				else
				{
					return *lIt < *rIt ;
				}
			}
			if( lIt == left.decimalPart.getEnd() && rIt != right.decimalPart.getEnd() )
			{
				return false;
			}
		}
		return true;
	}
	Boolean operator<( BigNumber const & left , BigNumber const & right )
	{
		return right > left;
	}
	Boolean operator<=( BigNumber const & left , BigNumber const & right )
	{
		return right >= left;
	}
}