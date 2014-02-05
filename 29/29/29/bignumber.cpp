//#include <cstdio>
//#include <cstdlib>
//#include <iostream>
//#include <sstream>


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <vector>

#include "bignumber.h"

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
		cout << "Destructing BigNumber (v = " << print(v) << ")." << endl;
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
			while(!last)
			{
				if(length <= lbase)
				{	
					char buffer[lbase+1] = {0};
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
					char buffer[lbase+1] = {0};
					strcpy(buffer, s.substr(length - lbase, lbase).c_str());
					int temp = atoi(buffer);
					newVector.push_back(temp);
					length -= lbase;
				}
			}
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
		vector<int> _printVector = printVector;
		if(!_printVector.empty())
		{
			cleanV(_printVector);
			ostringstream out;
			vector<int>::iterator iter = _printVector.end();
			out << *--iter;
			while( iter != _printVector.begin() )
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
			int numAdditions = 0;
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
		
		else if(a.back() < 0 && b.back() >= 0 || b.back() < 0 && a.back() >= 0)
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
			
			int numSubtractions = 0;
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
	vector<int> BigNumber::multiply(vector<int> a, int b)
	{
		bool negative = false;
		if(a.back() < 0 && b >= 0 || a.back() >= 0 && b < 0)
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
		if(a.back() < 0 && b.back() >= 0 || a.back() >= 0 && b.back() < 0)
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
		
		for(int i = 0; i < b.size(); i++)
		{
			vector<int> temp = multiply(a, b[i]);
			temp.insert(temp.begin(), i, 0);
			product = add(product, temp);
		}
		
		//Reattach negatives
		if(aNeg && !bNeg || !aNeg && bNeg)
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
		long offset = i - j;//this might create a limitation
		for(int k = 0; k <= offset; k++) //build quotient vector, all entries 0
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
		if(dividendNeg && !divisorNeg || !dividendNeg && divisorNeg)
		{
			quotient.back() *= -1;
			remainder.back() *= -1;
		}

		cout << print(dividend) << " / " 
			 << print(divisor) << " = " 
			 << print(quotient) << " R " 
			 << print(remainder) << endl;
			 
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
		cout << print(dividend) << " % " 
			 << print(divisor) << " = "
			 << print(remainder) << endl;
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
//		cout << "result: " <<  print(result) << endl;
		result.push_back(1);
//		cout << "result: " <<  print(result) << endl;
		for(int i = 0; lessThan(i, exp); i++)
		{
			vector<int> swap;
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
				int i = a.size() - 1;
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
		vector<int> _a = a;
		vector<int> _b = b;
		cleanV(_a);
		cleanV(_b);
		if(_a.size() == _b.size())
		{
			int i;
			for(i = _a.size()-1; i >= 0; i--)
			{
				if(_a[i] != _b[i])
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
	
	bool BigNumber::isPrime(){}
	bool BigNumber::isPrime(int n){}
	bool BigNumber::isPrime(string s){}
	bool BigNumber::isPrime(vector<int> vToCheck){}
	
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
		if(vectorToClean.size())
		{
			for(int i = 0; i < vectorToClean.size() && vectorToClean.back() == 0; i++)
			{
				vectorToClean.pop_back();
			}
		}
		if(vectorToClean.size() == 0)
		{
			vectorToClean.push_back(0);
		}
	}
}