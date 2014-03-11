#include <iostream>

#define EQUAL_THRESHOLD 0.00001

using namespace std;

namespace FMath
{
	class Fraction{    
		protected:        
			Fraction(Fraction& f){}
			int _num;        
			int _den;
			int _isSpecial;

		public:
			Fraction(){}  
			Fraction(int num, int den)
			{
				_isSpecial = -1;
				init(num, den);
			}
			void init(int num, int den)
			{
				if(den == 0)
				{
					cout << "Denominator cannot be 0." << endl;
					return;
				}
				_isSpecial = -1;
				_num = num;
				_den = den;
			}
			void out()        
			{            
				cout << _num << "/" << _den << endl;        
			}
			int num()
			{
				return _num;
			}
			int den()
			{
				return _den;
			}
			
			bool isSpecial();
			void multiplyBy(Fraction& f);
			void toLowestCommonTerms();
			
			
	};
	double abs(double val);
	bool areEqual(Fraction& a, Fraction& b);
	
};

void FMath::Fraction::toLowestCommonTerms()
{
	int i;
	while(true)
	{
		for(i = _num; i > 1; i--)
		// Begin with the highest numbers to reduce number
		// of repetitions.
		{
			if(!(_num % i) && !(_den % i))
			// i is a factor of both num and den
			{
				_num = _num / i;
				_den = _den / i;
				break;
			}
		}
		if(i == 1)
		// We have reduced as far as possible.
		{
			break; 
		}
	}
}

void FMath::Fraction::multiplyBy(Fraction& f)
{
	_num = _num*f.num();
	_den = _den*f.den();
}

bool FMath::Fraction::isSpecial()
{
	if(_isSpecial != -1)
	// The fraction was already checked
	{
		return _isSpecial;
	}
	/*
	if(num() >= den())
	// Only check fractions less than 0
	{
		_isSpecial = 0;
		return _isSpecial;
	}
	*/
	int numArr[2], denArr[2];
	numArr[0] = int(num()/10);
	numArr[1] = int(num()-numArr[0]*10);
	denArr[0] = int(den()/10);
	denArr[1] = int(den()-denArr[0]*10);
	// Eliminate trivial cases, where a zero exists in numerator
	// and denominator
	if (numArr[0] == 0 && denArr[0] == 0 ||
		numArr[0] == 0 && denArr[1] == 0 ||
		numArr[1] == 0 && denArr[0] == 0 ||
		numArr[1] == 0 && denArr[1] == 0)
	{
		return false;
	}
	// Check if digits can cancel, then test resulting fractions
	// for equality (non-trivial cases only).
	if(numArr[0] == denArr[0] && denArr[1] != 0)
	{
		Fraction f(numArr[1], denArr[1]);
		_isSpecial = FMath::areEqual(*this, f);
		return _isSpecial;
	}
	if(numArr[1] == denArr[0] && denArr[1] != 0)
	{
		Fraction f(numArr[0], denArr[1]);
		_isSpecial = FMath::areEqual(*this, f);
		return _isSpecial;
	}
	if(numArr[0] == denArr[1] && denArr[0] != 0)
	{
		Fraction f(numArr[1], denArr[0]);
		_isSpecial = FMath::areEqual(*this, f);
		return _isSpecial;
	}
	if(numArr[1] == denArr[1] && denArr[0] != 0)
	{
		Fraction f(numArr[0], denArr[0]);
		_isSpecial = FMath::areEqual(*this, f);
		return _isSpecial;
	}
	_isSpecial = 0;
	return _isSpecial;
}

double FMath::abs(double val)
{
	if(val < 0)
		return val*-1;
	return val;
}

bool FMath::areEqual(Fraction& a, Fraction& b)
{
	double da = double(a.num())/a.den();
	double db = double(b.num())/b.den();
	if(abs(da - db) < EQUAL_THRESHOLD)
		return true;
	return false;
}

int main()
{   
	// Use fraction p to keep a running multiplication
	FMath::Fraction p(1,1);
	FMath::Fraction f;
	
	// Iterate over all fractions with double digit
	// numerator and denominator, test whether they
	// are considered a special fraction
	for(int den = 11; den < 100; den++)
	{
		for(int num = 11; num < den; num++)
		{  
			f.init(num, den);
			if(f.isSpecial())
			{
				f.out();
				p.multiplyBy(f);
			}
		}
	}
	p.toLowestCommonTerms();
	
	// This will print the fraction p.  The denominator
	// is the answer to problem 33.
	cout << "----" << endl;
	p.out();
	return 0;
}	