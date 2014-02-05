#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
    long sum = 0;
    int n;
    for(n = 1; n < 1001; n++)
    {
        if(n % 2) //odd
        {
            sum += n*n;
        }
        else //even
        {
            sum += n*n + 1;
        }
        sum += n*n + n + 1;
    }
    
    // include the final square of n
    sum += n*n;
    
    cout << "The value of sum is: " << sum << endl;

    return 0;
}
