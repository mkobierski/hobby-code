namespace MK
{
	String::String()
	: count( 0 )
	{
	}

	String::String( char const * other )
	{
		data = other;
		count = data.length();
	}
	String::String( std::string const & other )
	{
		data = other;
		count = data.length();
	}

	String::String( F64 other )
	{
		// WARNING: INACCURACY OF DATA POSSIBLE IN CONVERSION FROM F64
		std::ostringstream sstream;
		sstream << std::setprecision( F64_DECIMAL_TRUNCATION + 1 ) << std::fixed << other;
		data = sstream.str();
		count = data.length();
	}
	String & String::operator=( String const & other )
	{
		String temp( other );
		swap( temp );
		return *this;
	}
	String::operator std::string()
	{
		return data;
	}

	void String::swap( String & other )
	{
		using std::swap;

		swap( data , other.data );
		swap( count , other.count );
	}

	std::string & String::get()
	{
		return data;
	}
	std::string const & String::get() const
	{
		return data;
	}

	Natural const String::getCount() const
	{
		return count;
	}
}