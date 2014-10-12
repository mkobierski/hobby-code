

namespace BigMath
{
	class BigNumber;
	class BigNumberImpl;

	std::string const getAsString( BigNumber const & );

	class BigNumber
	{
	public:
		BigNumber();
		~BigNumber();
		BigNumber( BigNumber const & );
		BigNumber & operator=( BigNumber const & );

		std::string const getAsString();

		void swap( BigNumber const & );

	private:
		void init( BigNumber const & );
		

		BigNumberImpl * impl;
	};


}