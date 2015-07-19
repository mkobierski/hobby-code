#ifndef UPINT_INCLUDED
#define UPINT_INCLUDED

#include <string>
#include <vector>

/* Notes:
    UPInt is an unlimited precision integer.

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

    Should allow functions to be passed a UPInt?

*/

namespace Math
{
    class UPInt
    {
        public:
            UPInt(); //done
            UPInt(std::string s); //done
            UPInt(int n); //done
            UPInt(vector<int> n); //done
            ~UPInt(); //placeholder?

        protected:

            UPInt(UPInt& b); //placeholder?
            UPInt& operator=(UPInt& b); //placeholder?

            static void swap(vector<int>& a, vector<int>& b); //done
            void cleanV(); //done
            static void cleanV(vector<int>& vectorToClean); //done
            static void setBase(int base, int lbase);

            std::deque<int> v;
    };
}

#endif // UPINT_INCLUDED
