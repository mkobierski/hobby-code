

namespace BigMath
{
	std::string const getAsString( BigNumber const & bn )
	{
		bn.getAsString();
	}

	BigNumber::BigNumber()
	:	impl( new BigNumberImpl )
	{
	}

	BigNumber::~BigNumber()
	{
		delete impl;
	}

	BigNumber::BigNumber( BigNumber const & rhs )
	:	impl( new BigNumberImpl )
	{
		
	}

	BigNumber & BigNumber::operator=( BigNumber const & rhs )
	{
		using std::swap;

		swap( rhs );
		return *this;
	}

	void BigNumber::init( BigNumber const & rhs )
	{
		BigNumber temp;
		temp.impl 


		swap();


	}

	void swap( BigNumber const & other )
}