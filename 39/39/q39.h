#ifndef Q39__INCLUDED
#define Q39__INCLUDED

namespace ProjectEuler39
{
	const unsigned MAX_PERIM = 1000;
	class RightTriangle
	{
	public:
		RightTriangle( unsigned a, unsigned b );

		bool const isValid() const;
		unsigned const perim() const { return a + b + c; }

		unsigned const getA() const { return a; }
		unsigned const getB() const { return b; }
		unsigned const getC() const { return c; }

		void print() const;
	private:
		static const double tol = 1e-6;
		unsigned a;
		unsigned b;
		unsigned c;
	};
}

#endif // Q39__INCLUDED