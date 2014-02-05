#include <stdlib.h>
#include <stdio.h>

int isPrime (long q);

long main () {
	int c = 0;
	long i;
	for (i = 2; c < 10001; i++)
		if (isPrime(i)) c++;
	printf ("%li\n",i - 1);

}

int isPrime (long q) {

	int i;
	for(i = 2; i < q; i++)
		if( q % i == 0 ) return 0;
	return 1;

}
