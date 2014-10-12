
namespace BigMath
{

    class BigNumberImpl
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
    
        BigNumberImpl();
		~BigNumberImpl();
        
		BigNumberImpl & operator=( BigNumberImpl & );
		BigNumberImpl & operator=( long long );
        BigNumberImpl & operator=( std::string );
        BigNumberImpl & operator=( char * );

		void set( char const * );
		void set( long long );
      	
      	std::string const getAsString() const;
        
        Byte * getBegin();
        Byte const * getBegin() const; 
        Byte * getEnd();
        Byte const * getEnd() const;
        Byte const * getEndLimit() const;

        Natural const getCount() const;

		bool isNegative() const;
		bool isZero() const;
		bool isValid();

        void clear();

    private:
        BigNumberImpl( BigNumberImpl & );
        
        
        void setNegative();
		void unsetNegative();
		void reverseNegative();
        
        Byte * handle;
        Natural count;
        Byte attributes;
        
        Natural numBlocks;
    };
}
