//#include <cstdio>
//#include <cstdlib>
//#include <iostream>
//#include <sstream>


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <cstring>
//#include <string>
#include <iomanip>
//#include <vector>

#include "BigNumber.h"

using namespace std;

namespace BigMath
{
	BigNumber::BigNumber()
	{
		v.clear();
		v.push_back(0);
	}

	BigNumber::BigNumber(string s)
	{
		
		v.clear();
		v = buildVector(s);
		cleanV();
	}
	
	BigNumber::BigNumber(int n)
	{
		v.clear();
		char buf[12] = {0};
		sprintf(buf, "%d", n);
		string s(buf);
		v = buildVector(s);
		cleanV();
	}
	
	BigNumber::BigNumber(vector<int> n)
	{
		v = n;
		cleanV();		
	}
	
	BigNumber::~BigNumber()
	{
		//cout << "Destructing BigNumber (v = " << print(v) << ")." << endl;
	}
	
	BigNumber::BigNumber(BigNumber& b)
	{
//		cout << "Copy constructor not implemented." << endl;
		vector<int> tempV = b.returnV();
		v = tempV;
		cleanV();
		cout << "Copying b (v = " << print(tempV) << ")." << endl;
	}
	
	BigNumber& BigNumber::operator=(BigNumber& b)
	{
//		cout << "operator=() not implemented." << endl;
		vector<int> tempV = b.returnV();
		v = tempV;
		cleanV();
		cout << "operator=(): b (v = " << print(tempV) << ")." << endl;
		return *this;
	}
	
/*	BigNumber BigNumber::operator+(vector<int> b)
	{
		cout << "In operator+(vector), summing." << endl;
	}
	
	BigNumber BigNumber::operator+(BigNumber b)
	{
		cout << "In operator+(BigNumber, BigNumber), summing." << endl;
		BigNumber returnNum;
		return returnNum;
	}*/
	
	vector<int> BigNumber::buildVector(int n)
	{
		char buf[12] = {0};
		sprintf(buf, "%d", n);
		string s(buf);
		return buildVector(s);
	}
	vector<int> BigNumber::buildVector(string& s)
	{
		bool negative = false;
		if(s[0] == '-')
		{
			negative = true;
			s.erase(0,1);
		}
		
		int length = s.length();

		bool last = false;
		vector<int> newVector;
		if(length > 0)
		{
			char *buffer = new char[lbase+1];
			while(!last)
			{
				for(int i = 0; i <= lbase; i++)
				{
					buffer[i] = 0;
				}
				if(length <= lbase)
				{
					strcpy(buffer, s.substr(0, length).c_str());
					int temp = atoi(buffer);
					newVector.push_back(temp);
					cleanV(newVector);
					if(negative)
					{
						newVector.back() *= -1;
					}
					last = true;
				}
				else
				{
					strcpy(buffer, s.substr(length - lbase, lbase).c_str());
					int temp = atoi(buffer);
					newVector.push_back(temp);
					length -= lbase;
				}
			}
			delete [] buffer;
		}
		return newVector;
	}
	
	string BigNumber::print()
	{	
		cleanV();
		string szV = print(v);
		return szV;
	}
/*	string BigNumber::print(vector<int> printVector)
	{
		vector<int> _printVector = printVector;
		return print(_printVector);
	} */
	string BigNumber::print(BigNumber& printNumber)
	{
		return printNumber.print();
	}
	string BigNumber::print(vector<int>& printVector)
	{
		if(!printVector.empty())
		{
			cleanV(printVector);
			ostringstream out;
			vector<int>::iterator iter = printVector.end();
			out << *--iter;
			while( iter != printVector.begin() )
			{
				out << setw(lbase)  <<  setfill('0')  << *--iter;
			}
			return out.str();
		}
		else
		{
			return "0 - Cannot print null vector";
		}
	}
	
	vector<int> BigNumber::returnV()
	{
		cleanV();
		return v;
	}
	
	vector<int> BigNumber::setV(int a)
	{
		vector<int> va = buildVector(a);
		return setV(va);
	}
	
	vector<int> BigNumber::setV(string a)
	{
		vector<int> va = buildVector(a);
		return setV(va);
	}
	
	vector<int> BigNumber::setV(vector<int> newV)
	{
		v = newV;
		cleanV();
		return v;
	}
	
	vector<int> BigNumber::add(int b)
	{
		vector<int> vb = buildVector(b);
		return add(vb);
	}
	vector<int> BigNumber::add(string s)
	{
		vector<int> vb = buildVector(s);
		return add(vb);
	}
	vector<int> BigNumber::add(vector<int>& b)
	{
		v = add(v, b);
		cleanV();
		return v;
	}
	vector<int> BigNumber::add(string a, string b)
	{
		vector<int> va = buildVector(a);
		vector<int> vb = buildVector(b);
		return add(va, vb);
	}
	vector<int> BigNumber::add(vector<int>& a, int b)
	{
		vector<int> vb = buildVector(b);
		return add(a, vb);
	}
	vector<int> BigNumber::add(int a, vector<int>& b)
	{
		vector<int> va = buildVector(a);
		return add(va, b);
	}
	vector<int> BigNumber::add(vector<int>& a, vector<int>& b)
	{
		vector<int> sum;
		add(a, b, sum);
		return sum;
	}
	vector<int> BigNumber::add(vector<int>& a, vector<int>& b, vector<int>& sum)
	{
		if (!sum.empty())
		{
			sum.clear();
		}

		cleanV(a);
		cleanV(b);
		
		if (a.back() >= 0 && b.back() >= 0)
		{ //positive case
			if (b.size() > a.size())
			{
				while(a.size() < b.size())
				{
					a.push_back(0);
				}
			}
			else
			{
				while(b.size() < a.size())
				{
					b.push_back(0);
				}
			}
			unsigned int numAdditions = 0;
			int carry = 0;
			while (numAdditions < a.size())
			{
				long current = a[numAdditions] + b[numAdditions] + carry;
				if(current >= base)
				{
					carry = 1;
					current = current - base;
				}
				else
				{
					carry = 0;
				}
				sum.push_back(current);
				numAdditions++;
			}
			if(carry)
			{
				sum.push_back(carry);
			}
			
			
	/*		cout << "\n" << print(a) ;
			cout << " + " << print ( b ) ;
			cout	 << " = " << print ( sum ) ;
			cout 	 << endl;	*/
		}
		
		else if( ( a.back() < 0 && b.back() >= 0 ) || ( b.back() < 0 && a.back() >= 0 ) )
		{ //one negative case
			//make a larger of two num
			if(a.size() == b.size())
			{
				int i = a.size() - 1;
				while(abs(a[i]) == abs(b[i]) && i > 0) //Modified this recently, didn't used to
				{									   //have the while loop	
					i--;
				}
				if(abs(a[i]) < abs(b[i]))
				{
					swap(a, b);
				}
			}
			else if(a.size() < b.size())
			{
				swap(a, b);
			}
			//now magnitude of a is larger than mag of b
			bool aNeg = false;
			if (a.back() < 0) //keep track of which num is negative
			{
				aNeg = true; //result will be negative
				a.back() = -a.back();
			}
			else
			{ //result will be positive
				b.back() = -b.back();
			}
			
			while(b.size() < a.size())
			{
				b.push_back(0);
			}
			
			unsigned int numSubtractions = 0;
			int borrow = 0;
			int aTemp = 0;
			while (numSubtractions < a.size())
			{
				long current;
				aTemp = a[numSubtractions];
				if(borrow != 0)
				{
					aTemp = aTemp - 1;
					borrow = 0;
				}
				
				if(aTemp < b[numSubtractions])
				{
					borrow = base;
					current = base + aTemp - b[numSubtractions];
				}
				else
				{
					current = aTemp - b[numSubtractions];
				}
				sum.push_back(current);
				numSubtractions++;
			}
			
			cleanV(a);
			cleanV(b);
			cleanV(sum);
			
			if(aNeg)
			{
				sum.back() = -sum.back();
				a.back() = -a.back();
				
	/*			cout << "\n" << print ( a ) 
				 	 << " + " << print ( b ) 
				 	 << " = " << print ( sum ) 
				 	 << endl;	*/
			}
			else
			{
	/*			cout << "\n" << print ( a ) 
			 		 << " - " << print ( b ) 
			 		 << " = " << print ( sum ) 
			 		 << endl;*/
			 		 
			 	b.back() = -b.back();
			}
		}
		
		//both negative?
		else if(a.back() < 0 && b.back() < 0)
		{
			a.back() = -a.back();
			b.back() = -b.back();
			add(a, b, sum);
			sum.back() = -sum.back();
			
	/*		cout << "\n-" << print(a) 
			 	 << " - " << print ( b ) 
			 	 << " = " << print ( sum ) 
				 << endl; */
		}
		return sum;
	}
	
	vector<int> BigNumber::multiply(int b)
	{
		vector<int> vb = buildVector(b);
		return multiply(vb);
	}
	vector<int> BigNumber::multiply(string s)
	{
		vector<int> vb = buildVector(s);
		return multiply(vb);
	}
	vector<int> BigNumber::multiply(vector<int>& b)
	{
		v = multiply(v, b);
		cleanV();
		return v;
	}
	vector<int> BigNumber::multiply(string a, string b)
	{
		vector<int> va = buildVector(a);
		vector<int> vb = buildVector(b);
		return multiply(va, vb);
	}
	vector<int> BigNumber::multiply(vector<int> a, int b)
	{
		bool negative = false;
		if( ( a.back() < 0 && b >= 0 ) || ( a.back() >= 0 && b < 0 ) )
		{
			if(a.back() < 0)
			{
				a.back() = -a.back();
			}
			else
			{
				b = -b;
			}
			negative = true;
		}
		else if(a.back() < 0 && b < 0)
		{
			a.back() = -a.back();
			b = -b;
		}
				
		int carry = 0;
		for (int i = 0; i < (int)a.size(); ++i)
		{
			long long cur = (long long)a[i] * b + carry;
			carry = cur / base;
			a[i] = cur % base;
		}
		if (carry > 0)
		{
			a.push_back(carry);
		}
		if(negative)
		{
			a.back() = -a.back();
		}
		return a;
	}
	vector<int> BigNumber::multiply(int a, vector<int>& b)
	{
		return multiply(b, a);
	}
	vector<int> BigNumber::multiply(vector<int>& a, vector<int>& b)
	{
		vector<int> product;
		multiply(a, b, product);
		return product;	
	}
	vector<int> BigNumber::multiply(vector<int>& a, vector<int>& b, vector<int>& product)
	{
		if (!product.empty())
		{
			product.clear();
		}
		cleanV(a);
		cleanV(b);
		
		//Strip negatives to facilitate multiplication
		bool aNeg = false;
		bool bNeg = false;
		if( ( a.back() < 0 && b.back() >= 0 ) || ( a.back() >= 0 && b.back() < 0 ) )
		{
			if(a.back() < 0)
			{
				a.back() = -a.back();
				aNeg = true;
			}
			else
			{
				b.back() = -b.back();
				bNeg = true;
			}
		}
		if(a.back() < 0 && b.back() < 0)
		{
			a.back() = -a.back();
			b.back() = -b.back();
			aNeg = bNeg = true;
		}
		
		for(unsigned int i = 0; i < b.size(); ++i)
		{
			vector<int> temp = multiply(a, b[i]);
			temp.insert(temp.begin(), i, 0);
			product = add(product, temp);
		}
		
		//Reattach negatives
		if( ( aNeg && !bNeg ) || ( !aNeg && bNeg ) )
		{
			product.back() = -product.back();
			if(aNeg)
			{
				a.back() = -a.back();
			}
			else
			{
				b.back() = -b.back();
			}
		}
		else if (aNeg && bNeg)
		{
			a.back() = -a.back();
			b.back() = -b.back();
		}
	//	cout << print(a) << " * " << print(b) << " = " << print(product) << endl;

		return product;
	}
	vector<int> BigNumber::subtract(int b)
	{
		vector<int> vb = buildVector(b);
		return subtract(vb);
	}
	vector<int> BigNumber::subtract(string s)
	{
		vector<int> vb = buildVector(s);
		return subtract(vb);
	}
	vector<int> BigNumber::subtract(vector<int>& b)
	{
		v = subtract(v, b);
		cleanV();
		return v;
	}
	vector<int> BigNumber::subtract(vector<int>& a, int b)
	{
		vector<int> vb = buildVector(b);
		return subtract(a, vb);
	}
	vector<int> BigNumber::subtract(int a, vector<int>& b)
	{
		vector<int> va = buildVector(a);
		return subtract(va, b);
	}
	vector<int> BigNumber::subtract(vector<int>& a, vector<int>& b)
	{
		vector<int> difference;
		subtract(a, b, difference);
		return difference;
	}
	vector<int> BigNumber::subtract(vector<int>& a, vector<int>& b, vector<int>& difference)
	{
		vector<int> cpb = b;
		cpb.back() = -cpb.back();
		return add(a, cpb, difference);
	}
	
	vector<int> BigNumber::divide(int b)
	{
		vector<int> vb = buildVector(b);
		return divide(vb);
	}
	vector<int> BigNumber::divide(string s)
	{
		vector<int> vs = buildVector(s);
		return divide(vs);
	}
	vector<int> BigNumber::divide(vector<int>& b)
	{
		v = divide(v, b);
		cleanV();
		return v;
	}
	vector<int> BigNumber::divide(std::string sza, std::string szb)
	{
		vector<int> va = buildVector(sza);
		vector<int> vb = buildVector(szb);
		return divide(va, vb);
	}
	vector<int> BigNumber::divide(vector<int>& dividend, vector<int>& divisor)
	{
		vector<int> quotient;
		return divide(dividend, divisor, quotient);
	}
	vector<int> BigNumber::divide(vector<int>& dividend, vector<int>& divisor, vector<int>& quotient)
	{
		vector<int> remainder;
		return divide(dividend, divisor, quotient, remainder);
	}
	vector<int> BigNumber::divide(vector<int>& dividend, vector<int>& divisor, vector<int>& quotient, vector<int>& remainder)
	{
		if (!quotient.empty())
		{
			quotient.clear();
		}
		if (!remainder.empty())
		{
			remainder.clear();
		}
		cleanV(dividend);
		cleanV(divisor);
		cleanV(quotient);
		cleanV(remainder); //it will now begin with 0 value
		
		if(divisor.size() == 1 && divisor[0] == 0)
		{
			cerr << "Error: cannot divide by 0." << endl;
			exit(1);
		}
		
		vector<int> _dividend = dividend;
		vector<int> _divisor = divisor;
		
		bool dividendNeg = false;
		bool divisorNeg = false;
		//Do some division stuff
		if(_dividend.back() < 0)
		{
			_dividend.back() *= -1;
			dividendNeg = true;
		}
		if(divisor.back() < 0)
		{
			_divisor.back() *= -1;
			divisorNeg = true;
		}

		int i = _dividend.size() - 1;
		int j = _divisor.size() - 1;
		unsigned long offset = i - j;//this might create a limitation
		for(unsigned int k = 0; k <= offset; k++) //build quotient vector, all entries 0
		{
			quotient.push_back(0);
		}
		vector<int> dividend_part;
		while(offset < _dividend.size())
		{
			dividend_part.push_back(_dividend[offset]);
			offset++;
		}
		offset = i - j; //recalculate offset
		//dividend_part should now be the same size as divisor
		remainder = _dividend;
		while(i >= j)
		{
			int m = 0;
			vector<int> mCompare = multiply((int)m, _divisor); //should be 0
			while(lessEqualThan(mCompare, dividend_part))
			{
				m++;
				mCompare = multiply((int)m, _divisor);
			}
			//previous to last m goes into quotient
			m--;
			quotient[offset] = m;
			vector<int> numToSubtract = multiply(m, _divisor);
			remainder = subtract(dividend_part, numToSubtract); //should always be positive
			cleanV(remainder);
			
			i--;
			offset = i - j;
			if(offset < 0)
			{
				break;
			}
			dividend_part = multiply(remainder, base);
			dividend_part[0] = _dividend[offset];
		}
		if( ( dividendNeg && !divisorNeg ) || ( !dividendNeg && divisorNeg ) )
		{
			quotient.back() *= -1;
			remainder.back() *= -1;
		}

		//cout << print(dividend) << " / " 
		//	 << print(divisor) << " = " 
		//	 << print(quotient) << " R " 
		//	 << print(remainder) << endl;
			 
		return quotient;
	}
	
	vector<int> BigNumber::modulus(int b)
	{
		vector<int> vb = buildVector(b);
		return modulus(vb);
	}
	vector<int> BigNumber::modulus(string s)
	{
		vector<int> vs = buildVector(s);
		return modulus(vs);
	} 
	vector<int> BigNumber::modulus(vector<int>& b)
	{
		v = modulus(v, b);
		cleanV();
		return v;
	}
	vector<int> BigNumber::modulus(string sza, string szb)
	{
		vector<int> va = buildVector(sza);
		vector<int> vb = buildVector(szb);
		return modulus(va, vb);
	}
	vector<int> BigNumber::modulus(vector<int>& dividend, vector<int>& divisor)
	{
		vector<int> quotient;
		return modulus(dividend, divisor, quotient);
	}
	vector<int> BigNumber::modulus(vector<int>& dividend, vector<int>& divisor, vector<int>& quotient)
	{
		vector<int> remainder;
		return modulus(dividend, divisor, quotient, remainder);
	}
	vector<int> BigNumber::modulus(vector<int>& dividend, vector<int>& divisor, vector<int>& quotient, vector<int>& remainder)
	{
		divide(dividend, divisor, quotient, remainder);
		//cout << print(dividend) << " % " 
		//	 << print(divisor) << " = "
		//	 << print(remainder) << endl;
		return remainder;
	}
			

	
	vector<int> BigNumber::big_pow(int b)
	{
		vector<int> vb = buildVector(b);
		return big_pow(vb);
	}
	vector<int> BigNumber::big_pow(string s)
	{
		vector<int> vb = buildVector(s);
		return big_pow(vb);
	}
	vector<int> BigNumber::big_pow(vector<int>& b)
	{
		v = big_pow(v, b);
		cleanV();
		return v;
	}
	vector<int> BigNumber::big_pow(vector<int>& exp_base, int exp)
	{
		vector<int> vexp = buildVector(exp);
		return big_pow(exp_base, vexp);
	}
	vector<int> BigNumber::big_pow(vector<int>& exp_base, vector<int>& exp)
	{
		vector<int> result;
		big_pow(exp_base, exp, result);
		return result;
	}
	vector<int> BigNumber::big_pow(vector<int>& exp_base, vector<int>& exp, vector<int>& result)
	{
		if (!result.empty())
		{
			result.clear();
		}
		cleanV(exp_base);
//		cout << "result: " <<  print(result) << endl;
		result = exp_base;
//		cout << "result: " <<  print(result) << endl;
		vector<int> swap;
		for(int i = 1; lessThan(i, exp); i++)
		{
			swap = multiply(result, exp_base);
	//		cout << "swap: " <<  print(swap) << endl;
			result = swap;
		}
		
		return result;
	}
	
	bool BigNumber::lessThan(int b)
	{
		vector<int> vb = buildVector(b);
		return lessThan(vb);
	}
	bool BigNumber::lessThan(string s)
	{
		vector<int> vb = buildVector(s);
		return lessThan(vb);
	}
	bool BigNumber::lessThan(vector<int>& b)
	{
		return lessThan(v, b);
	}
	bool BigNumber::lessThan (int a, vector<int>& b)
	{
		vector<int> va = buildVector(a);
		return lessThan(va, b);
	}
	bool BigNumber::lessThan (vector<int>& a, int b)
	{
		vector<int> vb = buildVector(b);
		return lessThan(a, vb);
	}
	bool BigNumber::lessThan (string s, vector<int>& b)
	{
		vector<int> va = buildVector(s);
		return lessThan(va, b);
	}
	bool BigNumber::lessThan (vector<int>& a, string s)
	{
		vector<int> vb = buildVector(s);
		return lessThan(a, vb);
	}
	bool BigNumber::lessThan (string sza, string szb)
	{
		vector<int> va = buildVector(sza);
		vector<int> vb = buildVector(szb);
		return lessThan(va, vb);
	}
	bool BigNumber::lessThan (vector<int>& a, vector<int>& b)
	{
		cleanV(a);
		cleanV(b);
		if(a.size() == b.size())
		{ //four cases depending on positive/negative
			if(a.back() < 0 && b.back() >= 0)
			{
				return true;
			}
			else if(a.back() >= 0 && b.back() < 0)
			{
				return false;
			}
			else if(a.back() < 0 && b.back() < 0)
			{
				unsigned int i = a.size() - 1;
				while(a[i] == b[i] && i > 0)
				{
					i--;
				}
				if(i == a.size() - 1)
				{
					if(a[i] < b[i])
					{
						return true;
					}
				}
				else
				{
					if(a[i] > b[i])
					{
						return true;
					}
				}
				return false;
			}
			else if(a.back() >= 0 && b.back() >= 0)
			{
				int i = a.size() - 1;
				while(a[i] == b[i] && i > 0)
				{
					i--;
				}
				if(a[i] < b[i])
				{
					return true;
				}
				return false;
			}
		}
		if(b.size() > a.size() && b.back() > 0)
		{
			return true;
		}
		if(a.size() > b.size() && a.back() < 0)
		{
			return true;
		}
		return false;
	}

	bool BigNumber::lessEqualThan(int b)
	{
		vector<int> vb = buildVector(b);
		return lessEqualThan(vb);
	}
	bool BigNumber::lessEqualThan(std::string s)
	{
		vector<int> vs = buildVector(s);
		return lessEqualThan(vs);
	}
	bool BigNumber::lessEqualThan(vector<int>& b)
	{
		return lessEqualThan(v, b);
	}
	bool BigNumber::lessEqualThan(int a, vector<int>& b)
	{
		vector<int> va = buildVector(a);
		return lessEqualThan(va, b);
	}
	bool BigNumber::lessEqualThan(vector<int>& a, int b)
	{
		vector<int> vb = buildVector(b);
		return lessEqualThan(a, vb);
	}
	bool BigNumber::lessEqualThan(std::string s, vector<int>& b)
	{
		vector<int> va = buildVector(s);
		return lessEqualThan(va, b);
	}
	bool BigNumber::lessEqualThan(vector<int>& a, std::string s)
	{
		vector<int> vb = buildVector(s);
		return lessEqualThan(a, vb);
	}
	bool BigNumber::lessEqualThan(std::string sza, std::string szb)
	{
		vector<int> va = buildVector(sza);
		vector<int> vb = buildVector(szb);
		return lessEqualThan(va, vb);
	}
	bool BigNumber::lessEqualThan(vector<int>& a, vector<int>& b)
	{
		vector<int> _a = a;
		vector<int> _b = b;
		vector<int> aMinusOne = subtract(_a,1);
		return lessThan(aMinusOne, _b);
	}
	
	bool BigNumber::greaterThan(int b)
	{
		vector<int> vb = buildVector(b);
		return greaterThan(vb);
	}
	bool BigNumber::greaterThan(string s)
	{
		vector<int> vb = buildVector(s);
		return greaterThan(vb);
	}
	bool BigNumber::greaterThan(vector<int>& b)
	{
		return greaterThan(v, b);
	}
	bool BigNumber::greaterThan (int a, vector<int>& b)
	{
		vector<int> va = buildVector(a);
		return greaterThan(va, b);
	}
	bool BigNumber::greaterThan (vector<int>& a, int b)
	{
		vector<int> vb = buildVector(b);
		return greaterThan(a, vb);
	}
	bool BigNumber::greaterThan (string s, vector<int>& b)
	{
		vector<int> va = buildVector(s);
		return greaterThan(va, b);
	}
	bool BigNumber::greaterThan (vector<int>& a, string s)
	{
		vector<int> vb = buildVector(s);
		return greaterThan(a, vb);
	}
	bool BigNumber::greaterThan (string sza, string szb)
	{
		vector<int> va = buildVector(sza);
		vector<int> vb = buildVector(szb);
		return greaterThan(va, vb);
	}
	bool BigNumber::greaterThan (vector<int>& a, vector<int>& b)
	{
		return !lessEqualThan(a, b);
	}
	
	bool BigNumber::greaterEqualThan(int b)
	{
		vector<int> vb = buildVector(b);
		return greaterEqualThan(vb);
	}
	bool BigNumber::greaterEqualThan(std::string s)
	{
		vector<int> vs = buildVector(s);
		return greaterEqualThan(vs);
	}
	bool BigNumber::greaterEqualThan(vector<int>& b)
	{
		return greaterEqualThan(v, b);
	}
	bool BigNumber::greaterEqualThan(int a, vector<int>& b)
	{
		vector<int> va = buildVector(a);
		return greaterEqualThan(va, b);
	}
	bool BigNumber::greaterEqualThan(vector<int>& a, int b)
	{
		vector<int> vb = buildVector(b);
		return greaterEqualThan(a, vb);
	}
	bool BigNumber::greaterEqualThan(std::string s, vector<int>& b)
	{
		vector<int> va = buildVector(s);
		return greaterEqualThan(va, b);
	}
	bool BigNumber::greaterEqualThan(vector<int>& a, std::string s)
	{
		vector<int> vb = buildVector(s);
		return greaterEqualThan(a, vb);
	}
	bool BigNumber::greaterEqualThan(std::string sza, std::string szb)
	{
		vector<int> va = buildVector(sza);
		vector<int> vb = buildVector(szb);
		return greaterEqualThan(va, vb);
	}
	bool BigNumber::greaterEqualThan(vector<int>& a, vector<int>& b)
	{
		return !lessThan(a, b);
	}
	
	bool BigNumber::equalTo(int b)
	{
		vector<int> vb = buildVector(b);
		return equalTo(vb);
	}
	bool BigNumber::equalTo(string s)
	{
		vector<int> vs = buildVector(s);
		return equalTo(vs);
	}
	bool BigNumber::equalTo(vector<int>& b)
	{
		return equalTo(v, b);
	}
	bool BigNumber::equalTo(int a, vector<int>& b)
	{
		vector<int> va = buildVector(a);
		return equalTo(va, b);
	}
	bool BigNumber::equalTo(vector<int>& a, int b)
	{
		vector<int> vb = buildVector(b);
		return equalTo(a, vb);
	}
	bool BigNumber::equalTo(string s, vector<int>& b)
	{
		vector<int> vs = buildVector(s);
		return equalTo(vs, b);
	}
	bool BigNumber::equalTo(vector<int>& a, string s)
	{
		return equalTo(s, a);
	}
	bool BigNumber::equalTo(string sza, string szb)
	{
		vector<int> va = buildVector(sza);
		vector<int> vb = buildVector(szb);
		return equalTo(va, vb);
	}
	bool BigNumber::equalTo(vector<int>& a, vector<int>& b)
	{
		cleanV(a);
		cleanV(b);
		if(a.size() == b.size())
		{
			int i;
			for(i = a.size() - 1; i >= 0; i--)
			{
				if(a[i] != b[i])
				{
					break;
				}
			}
			if(i == -1)
			{
				return true;
			}
		}
		return false;
	}
	
	bool BigNumber::isPrime()
	{
		cleanV();
		return isPrime(v);
	}
	bool BigNumber::isPrime(int n)
	{
		vector<int> vn = buildVector(n);
		return isPrime(vn);
	}
	bool BigNumber::isPrime(string s)
	{
		vector<int> vs = buildVector(s);
		return isPrime(vs);
	}
	bool BigNumber::isPrime(vector<int> vToCheck) //TODO: this breaks, first value is 15.
	{
		//find square root, trial and error
		cleanV(vToCheck);
		if (vToCheck.back() < 0)
		{
			vToCheck.back() *= -1;
		}
		if( equalTo( vToCheck , 1 ) )
		{
			return false;
		}
		if( equalTo( vToCheck , 2 ) )
		{
			return true;
		}
		
		vector<int> i;
		i.push_back(1);
		vector<int> power = big_pow(i,2);
		while(lessEqualThan(power, vToCheck))
		{
			i = add(i, 1);
			power = big_pow(i, 2);
			if(equalTo(power, vToCheck))
			{
				return false;
			}
		}
		
		
		//last previous iteration was last smallest
		i = subtract(i, 1);
		
		//now I is integer square root
		//build char vector to form a seive, size of i
		string sieve;
		sieve.push_back('0'); //first element is 1, don't test as it will have 0 remainder
		while (lessThan(sieve.size(), i))
		{
			sieve.push_back('1');
			if(sieve.size() > 0xFFFE)
			{
				cout << "Sieve bigger than Int size, unpredictable results follow." << endl;
			}
		}
		i = buildVector(1);
		string::iterator iter = sieve.begin(); //first can represent number 1;
		string::iterator iterSkip;
		vector<int> remainder;
		vector<int> iterCounter;
		while(*iter)
		{
			if(*iter == '1')
			{
				//check if vToCheck is divisible by
				remainder = modulus(vToCheck, i);
				if(equalTo(remainder, 0))
				{
					return false;
				}
				else
				{
					//skip iter through at intervals of i and set sieve to 0
					iterSkip = iter;
					iterCounter = i;
					while(*iterSkip)
					{
						if(equalTo(iterCounter, i))
						{
							*iterSkip = '0';
							iterSkip++;
							iterCounter = buildVector(1);
						}
						else
						{
							iterSkip++;
							iterCounter = add(iterCounter, 1);
						}
					}
				}
			}
			//cout << "i: " << print(i) << endl;
			iter++;
			i = add(i, 1);
		}
		
		return true;
		
		
	}
	
	bool BigNumber::isCircularPrime()
	{
		cleanV();
		// Convert v to base 10, one number per vector element
		return isCircularPrime(v);
	}
	bool BigNumber::isCircularPrime(int n)
	{
		setBase(10, 1);
		vector<int> vn = buildVector(n);
		return isCircularPrime(vn);
	}
	bool BigNumber::isCircularPrime(std::string s)
	{
		vector<int> vs = buildVector(s);
		return isCircularPrime(vs);
	}
	bool BigNumber::isCircularPrime(vector<int> vToCheck)
	{
		// A circular prime number is a number which is prime for
		// every rotation of its digits.
		// Ex. 197, 971, and 719 are all prime
		//
		// Use base of 10 so only 1 digit is stored per vector element
		cleanV(vToCheck);
		string sv = print(vToCheck);
		setBase(10, 1);
		vector<int> v_size_checker = buildVector(sv);
		unsigned int v_size = v_size_checker.size();
		
		int prev_base = base;
		int prev_lbase = lbase;
		int comp_base = 10;
		int comp_lbase = 1;
		
		sv = print(vToCheck);
		setBase(comp_base, comp_lbase);
		vToCheck=buildVector(sv);
		if(v_size > 1)
		// Single digit numbers don't follow this check...
		// 2 is considered circular prime
		{
			for(unsigned int i = 0; i < v_size; i++)
			{
				// If any digit of the number is even or 5, it
				// cannot be a circular prime.
				switch(vToCheck[i])
				{
					case 0:
					case 2:
					case 4:
					case 5:
					case 6:
					case 8:
						return false;
				}
			}
		}
		for(unsigned int i = 0; i < v_size; i++)
		{
			if(!isPrime(vToCheck))
			{
				return false;
			}
			// Rotate the number
			sv = print(vToCheck);
			setBase(comp_base, comp_lbase);
			vToCheck=buildVector(sv);
			
			// Rotate the number
			int lastNum = vToCheck.back();
			for(int i = v_size - 1; i > 0; i--)
			{
				vToCheck[i] = vToCheck[i-1];
			}
			vToCheck[0] = lastNum;
			
			sv = print(vToCheck);
			setBase(prev_base, prev_lbase);
			vToCheck=buildVector(sv);
			if(vToCheck.size() != v_size)
			{
				cout << "Error - size has changed!" << endl;
				exit(1);
			}
		}
		return true;
	}
	
	bool BigNumber::isTruncatablePrime()
	{
		cleanV();
		return isTruncatablePrime( v );
	}
	bool BigNumber::isTruncatablePrime( int n )
	{
		setBase( 10 , 1 );
		vector< int > vn = buildVector( n );
		return isTruncatablePrime( vn );
	}
	bool BigNumber::isTruncatablePrime(std::string s)
	{
		vector< int > vs = buildVector( s );
		return isTruncatablePrime( vs );
	}
	bool BigNumber::isTruncatablePrime(vector<int> vToCheck)
	{
		// A truncatable prime number is a number which remains prime when
		// its leading or trailing digits are stripped until only one digit
		// remains.
		// Ex. 3797, 797, 97, and 7 are prime
		// 	   3797, 379, 37, and 3 are prime
		//
		// Use base of 10 so only 1 digit is stored per vector element
		cleanV(vToCheck);
		string sv = print(vToCheck);
		setBase(10, 1);
		vector<int> v_size_checker = buildVector(sv);
		unsigned int v_size = v_size_checker.size();
		
		// int prev_base = base;
		// int prev_lbase = lbase;
		int comp_base = 10;
		int comp_lbase = 1;
		
		sv = print(vToCheck);
		setBase(comp_base, comp_lbase);
		vToCheck=buildVector(sv);
		if( v_size <= 0 )
		{
			return false;
		}
		if( v_size == 1 )
		{
			switch( vToCheck[0] )
			{
				case 0:
				case 1:
				case 2:
				case 3:
				case 5:
				case 7:
					return false; 
			}
		}
		else
		{
			// A number with 5 or a multiple of 2 in it (with exception
			// of the most significant digit) cannot be a truncatable prime
			for( unsigned int i = 0 ; i < vToCheck.size() - 1 ; ++i )
			{
				switch( vToCheck[i] )
				{
					case 0:
					case 2:
					case 4:
					case 5:
					case 6:
					case 8:
						return false;
				}
			}
		}
		
		vector< int > vToCheckOrig = vToCheck;
		BigNumber out;
		for( unsigned int i = 0 ; i < v_size ; ++i )
		{
			out.setV( vToCheck );
			// cout << out.print() << " : Checking...\n" ;
			if( !isPrime( vToCheck ) )
			{
				return false;
			}
			// cout << "    " << out.print() << endl;
			
			// Truncate last digit
			vToCheck.pop_back();
		}
		
		
		// cout << "Passed first iteration\n";
		vToCheck = vToCheckOrig;
		
		for( unsigned int i = 0 ; i < v_size - 1; ++i )
		{
			// Shift digits forward by 1
			for( unsigned int j = 0 ; j < vToCheck.size() - 1 ; ++j )
			{
				vToCheck[ j ] = vToCheck[ j + 1 ];
			}
			vToCheck.pop_back();
			
			out.setV( vToCheck );
			if( !isPrime( vToCheck ) )
			{
				return false;
			}
			// cout << "    " << out.print() << endl;
		}
		return true;
	}
	
	vector<int> BigNumber::factorial()
	{
		cleanV();
		return factorial(v);
	}
	vector<int> BigNumber::factorial(int n)
	{
		vector<int> vn = buildVector(n);
		return factorial(vn);
	}
	vector<int> BigNumber::factorial(string s)
	{
		vector<int> vs = buildVector(s);
		return factorial(vs);
	}
	vector<int> BigNumber::factorial(vector<int> n)
	{
		if(n.back() < 0)
		{
			cout << "Cannot factorial a negative number: " << print(n) << endl;
			return buildVector(-1);
		}
		else
		{
			if(n.size() == 1 && n.back() == 0)
			{
				return buildVector(1);
			}
			else
			{
				vector<int> one = buildVector(1);
				vector<int> nextN = factorial(subtract(n,one));
				return multiply(n, nextN);
			}
		}
		cout << "Factorial: Shouldn't arrive here!" << endl;
		exit(1);
	}
	
	vector<int> BigNumber::big_abs()
	{
		vector<int> _v = v;
		if(_v.back() < 0)
		{
			_v.back() = -_v.back();
		}
		return _v;
	}
	vector<int> BigNumber::big_abs(int n)
	{
		vector<int> vn;
		if(n < 0)
		{
			vn = buildVector(-n);
		}
		else
		{
			vn = buildVector(n);
		}
		return vn;
	}
	vector<int> BigNumber::big_abs(std::string s)
	{
		vector<int> vs = buildVector(s);
		if (vs.back() < 0)
		{
			vs.back() = -vs.back();
		}
		return vs;
	}
	vector<int> BigNumber::big_abs(vector<int>& n)
	{
		vector<int> _n = n;
		cleanV(_n);
		if(_n.back() < 0)
		{
			_n.back() = -_n.back();
		}
		return _n;
	}
	
	void BigNumber::swap(vector<int>& a, vector<int>& b)
	{
		vector<int> temp = a;
		a = b;
		b = temp;
	}
	
	void BigNumber::cleanV()
	{
		cleanV(v);
	}
	void BigNumber::cleanV(vector<int>& vectorToClean)
	{
		size_t size = vectorToClean.size();
		if( size )
		{
			for(unsigned int i = 0; i < vectorToClean.size() && vectorToClean.back() == 0; i++)
			{
				vectorToClean.pop_back();
			}
		}
		if(vectorToClean.size() == 0)
		{
			vectorToClean.push_back(0);
		}
	}

	void BigNumber::setBase(int base, int lbase)
	{
		BigNumber::base = base;
		BigNumber::lbase = lbase;
	}
	
	int BigNumber::base = DEFAULT_BASE;
	int BigNumber::lbase = DEFAULT_LBASE;
}
