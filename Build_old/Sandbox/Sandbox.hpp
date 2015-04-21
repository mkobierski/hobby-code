
class A
{
public:
	A(){}
	~A(){}
	A( A const & );
	A const & operator=( A const & );

private:
	std::string data;
};