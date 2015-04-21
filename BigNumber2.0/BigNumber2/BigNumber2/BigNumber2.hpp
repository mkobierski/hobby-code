

namespace BigMath
{
	const static Natural BLOCK_SIZE = 512;

	class BigNumber
    {
    public:
    	struct Mask
    	{
	    	enum 
	    	{
	    		NEGATIVE = 1 << 7 ,
	    		DECIMAL = 1 << 6
	    	};
    	};
    
        BigNumber();
		~BigNumber();

		template< typename T >
			BigNumber( T const & other )
			{
				init();
				set( other );
			}
		BigNumber( BigNumber const & );

		BigNumber & operator=( BigNumber const & );
		template< typename T >
			BigNumber & operator=( T const & other )
			{
				set( other );
				return *this;
			}

		void init();
        void swap( BigNumber & );

		void set( MK::String const & );
		//void set( std::string );
		//void set( char const * );
		void set( double );
		void set( long long );
      	
		// BigNumber operator+( BigNumber const & );

      	std::string const getAsString() const;

		bool const isNegative() const;
		bool const isZero() const;
		bool const isValid();

		bool const hasDecimal() const;

		Byte viewAttributes() const { return attributes; }

    private:
       
        void setNegative();
		void unsetNegative();
		void reverseNegative();

		void setHasDecimal();
		void unsetHasDecimal();

		friend BigNumber operator+( BigNumber const & , BigNumber const & );
		friend BigNumber operator-( BigNumber const & , BigNumber const & );

		friend Boolean operator==( BigNumber const & , BigNumber const & );
		friend Boolean operator>(  BigNumber const & , BigNumber const & );
		friend Boolean operator>=( BigNumber const & , BigNumber const & );

        Byte attributes;

		BigNumericalData wholePart;
		BigNumericalData decimalPart;
    };

	BigNumber operator+( BigNumber const & , BigNumber const & );
    // BigNumber operator-( BigNumber const & , BigNumber const & );

	Boolean operator==( BigNumber const & , BigNumber const & );
	Boolean operator!=( BigNumber const & , BigNumber const & );
	Boolean operator>( BigNumber const & , BigNumber const & );
	Boolean operator>=( BigNumber const & , BigNumber const & );
	Boolean operator<( BigNumber const & , BigNumber const & );
	Boolean operator<=( BigNumber const & , BigNumber const & );

    std::string const getAsString( BigNumber const & );
}