#include <stdio.h>
#include <stdlib.h>

int isPrime (long q);

int main () {

	const long multiple = 600851475143;
	long primeFactor = 1;

	int i;
	for (i = 2; i < multiple; i++) {
		if( multiple % i == 0  && isPrime(i) ) printf ("prime factor : %i\n",i);
		
	} 

	/*
	for (i = 2; i < 25; i++)
	printf ("%i : %i\n", i, isPrime(i));
	//    */

}

int isPrime (long q) {

	int i;
	for(i = 2; i < q; i++)
		if( q % i == 0 ) return 0;
	return 1;

}
