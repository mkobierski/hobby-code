#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LIM 2000000

int isPrime (long q);

int main () {

	long sum;
	
	int i;
	for (i = 2; i < LIM; i++)
		if(isPrime((long)i)) {
			sum = sum + i;
			printf ("i: %i sum: %li\n",i,sum);
		}

	printf ("%li\n", sum);

	return 0;
}

int isPrime (long q) {

	double sqrtOfQ = sqrt (q);
	int i;
	if (q == 2) return 1;
	if (q != 2 && q % 2 == 0) return 0;
	for(i = 3; i <= sqrtOfQ; i+=2)
		if( q % i == 0 ) return 0;
	return 1;

}
