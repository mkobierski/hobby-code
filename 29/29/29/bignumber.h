#ifndef _bigmath_
#define _bigmath_

#include <string>
#include <vector>

using std::vector;

/* Notes:
	should be able use the static functions by inputting strings - overload for two string args?
	power does not handle negative exponents
	Should implement comparison operators
	Make arguments const, and copy to local var to manipulate (negatives etc)
	
	I should start making versions, as a lot of things work very well!
	This thing is broken recently as operator+ etc. and copy constructor were implemented
	Have to look into how to do that properly.
	
	Need to implement vector comparison for use in computing big_pow
	Should make abs()
	
	Divide is implemented with remainder
	TEST LESSEQUALTHAN
	Implement some equalsTo
	
	Some functions perform other than expected due to passing by reference
	(values of original numbers are modified when maybe they should 
	be treated as const instead..?)
	
*/

namespace BigMath
{
	class BigNumber
	{
		public:
			BigNumber(); //done
			BigNumber(std::string s); //done
			BigNumber(int n); //done
			BigNumber(vector<int> n); //done
			~BigNumber(); //placeholder?
			
//			BigNumber operator+(vector<int> b);
//			BigNumber operator+(BigNumber b);
			
			static vector<int> buildVector(int n); //done
			static vector<int> buildVector(std::string& s); //done
			
			vector<int> add(int b); //done
			vector<int> add(std::string s);
			vector<int> add(vector<int>& b); //done
			static vector<int> add(std::string a, std::string b);
			static vector<int> add(vector<int>& a, vector<int>& b); //done
			static vector<int> add(vector<int>& a, vector<int>& b, vector<int>& sum); //done
			
			vector<int> multiply(int b); //done
			vector<int> multiply(std::string s); //done
			vector<int> multiply(vector<int>& b); //done
			static vector<int> multiply(vector<int> a, int b); //done
			static vector<int> multiply(int a, vector<int>& b);
			static vector<int> multiply(vector<int>& a, vector<int>& b); //done
			static vector<int> multiply(vector<int>& a, vector<int>& b, vector<int>& product); //done

			vector<int> subtract(int b); //done
			vector<int> subtract(std::string s); //done
			vector<int> subtract(vector<int>& b); //done
			static vector<int> subtract(vector<int>& a, int b);
			static vector<int> subtract(int a, vector<int>& b);
			static vector<int> subtract(vector<int>& a, vector<int>& b); //done
			static vector<int> subtract(vector<int>& a, vector<int>& b, vector<int>& difference); //done
			
			vector<int> divide(int b);//done
			vector<int> divide(std::string s); //done
			vector<int> divide(vector<int>& b);	//done	
			static vector<int> divide(std::string sza, std::string szb);	
			static vector<int> divide(vector<int>& dividend, vector<int>& divisor); //done
			static vector<int> divide(vector<int>& dividend, vector<int>& divisor, vector<int>& quotient); //done
			static vector<int> divide(vector<int>& dividend, vector<int>& divisor, vector<int>& quotient, vector<int>& remainder); //done
			
			vector<int> modulus(int b); //done
			vector<int> modulus(std::string s); //done
			vector<int> modulus(vector<int>& b);	//done	
			static vector<int> modulus(std::string sza, std::string szb);	
			static vector<int> modulus(vector<int>& dividend, vector<int>& divisor); //done
			static vector<int> modulus(vector<int>& dividend, vector<int>& divisor, vector<int>& quotient); //done
			static vector<int> modulus(vector<int>& dividend, vector<int>& divisor, vector<int>& quotient, vector<int>& remainder); //done
			
			vector<int> big_pow(int b); //done
			vector<int> big_pow(std::string s); //done
			vector<int> big_pow(vector<int>& b); //done
			static vector<int> big_pow(vector<int>& exp_base, vector<int>& exp); //done
			static vector<int> big_pow(vector<int>& exp_base, vector<int>& exp, vector<int>& result); //done
			
			bool lessThan(int b); //done
			bool lessThan(std::string s); //done
			bool lessThan(vector<int>& b); //done
			static bool lessThan (int a, vector<int>& b); //done
			static bool lessThan (vector<int>& a, int b); //done
			static bool lessThan (std::string s, vector<int>& b); //done
			static bool lessThan (vector<int>& a, std::string s); //done
			static bool lessThan (std::string sza, std::string szb); //done
			static bool lessThan (vector<int>& a, vector<int>& b); //done
			
			bool lessEqualThan(int b); //done
			bool lessEqualThan(std::string s); //done
			bool lessEqualThan(vector<int>& b); //done
			static bool lessEqualThan (int a, vector<int>& b); //done
			static bool lessEqualThan (vector<int>& a, int b); //done
			static bool lessEqualThan (std::string s, vector<int>& b); //done
			static bool lessEqualThan (vector<int>& a, std::string s); //done
			static bool lessEqualThan (std::string sza, std::string szb); //done
			static bool lessEqualThan (vector<int>& a, vector<int>& b); //done
			
			bool equalTo(int b); //done
			bool equalTo(std::string s); //done
			bool equalTo(vector<int>& b); //done
			static bool equalTo (int a, vector<int>& b); //done
			static bool equalTo (vector<int>& a, int b); //done
			static bool equalTo (std::string s, vector<int>& b); //done
			static bool equalTo (vector<int>& a, std::string s); //done
			static bool equalTo (std::string sza, std::string szb); //done
			static bool equalTo (vector<int>& a, vector<int>& b); //done
			
			bool isPrime();
			bool isPrime(int n);
			bool isPrime(std::string s);
			bool isPrime(vector<int> vToCheck);
			
			vector<int> factorial(); //done
			static vector<int> factorial(int n); //done
			static vector<int> factorial(std::string s); //done
			static vector<int> factorial(vector<int> n); //done (this function is recursive, paramer isn't by reference

			std::string print(); //done
			static std::string print(BigNumber& printNumber); //done
			static std::string print(vector<int>& printVector); //done
//			static std::string print(vector<int> printVector); //check if this is required even..
			
			vector<int> big_abs(); //done
			static vector<int> big_abs(int n); //done
			static vector<int> big_abs(std::string s); //done
			static vector<int> big_abs(vector<int>& n); //done
			
			vector<int> returnV(); //done
			
			vector<int> setV(int a); //done
			vector<int> setV(std::string a); //done
			vector<int> setV(vector<int> newV); //done
			
		protected:
			
			BigNumber(BigNumber& b); //placeholder?
			BigNumber& operator=(BigNumber& b); //placeholder?
			
			static void swap(vector<int>& a, vector<int>& b); //done
			void cleanV(); //done
			static void cleanV(vector<int>& vectorToClean); //done
			
			vector<int> v;
			static const int base = 100//1000 * 1000 * 1000;
			static const int lbase = 2//9;
	};
}

#endif