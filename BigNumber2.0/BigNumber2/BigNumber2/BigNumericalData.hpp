// No header guard, only included in 
namespace BigMath
{
    class BigNumericalData {
	public:
		BigNumericalData();
		~BigNumericalData();
		BigNumericalData( BigNumericalData const & other );
		BigNumericalData & operator=( BigNumericalData const & other );

		void init( Natural _numBlocks = 1 );
		void reset();
		void swap( BigNumericalData & );


		bool const isInitialized() const;
		bool const isZero() const;

		Byte * getBegin();
        Byte const * getBegin() const; 
        Byte * getEnd();
        Byte const * getEnd() const;
        Byte const * const getEndLimit() const;

		Natural count;

	private:
		Byte * handle;
		Natural numBlocks;
	};

	Boolean operator==( BigNumericalData const & , BigNumericalData const & );
}
