#include "Prime/PrimeSeive.hpp"

int main() {
    // This is OK
    PrimeSeive<2> ps;
    ps.check(1);
    
    // This is NOT OK
    //
    // PrimeSeive<1> ps1;
    // bool res1 = ps1.check(0);
    return 0;
}