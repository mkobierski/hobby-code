#ifndef BIGNUMBER2__INCLUDED
#define BIGNUMBER2__INCLUDED

#include "Types.hpp"

namespace Memory
{
	void * allocate( Natural bytes );
	void * zeroRange( void * handle , Natural bytes );
	void freeRange( void * handle );
}

namespace BigMath
{
	class BigNumber;
	
	std::string const getAsString( BigNumber const & );

    class BigNumber
    {
    	enum{ BLOCK_SIZE = 1024 };
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
        
        BigNumber & operator=( long long );
        BigNumber & operator=( std::string );
        BigNumber & operator=( char * );
      	
      	std::string const getAsString() const;
        
        Byte * getBegin();
        Byte const * getBegin() const; 
        Byte * getEnd();
        Byte const * getEnd() const;
        Byte const * getEndLimit() const;

        Natural const getCount() const;

		bool isNegative() const;
		bool isEmpty() const;
		bool isValid();

        void clear();

    private:
        BigNumber( BigNumber & );
        BigNumber & operator=( BigNumber & );
        
        void setNegative();
		void unsetNegative();
		void reverseNegative();
        
        Byte * handle;
        Natural count;
        bool negative;
        
        Natural numBlocks;
    };
}

#endif // BIGNUMBER2__INCLUDED
