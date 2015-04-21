namespace MK
{
	class String
	{
		const Natural F64_DECIMAL_TRUNCATION = 16;
	public:
		String();
		String( char const * );
		String( std::string const & );
		String( F64 );
		String & operator=( String const & other );
		
		operator std::string();

		void swap( String & );

		std::string & get();
		std::string const & get() const;

		Natural const getCount() const;

	private:
		std::string data;
		Natural count;
	};
}