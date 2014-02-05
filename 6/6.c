#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMBER 100



long sumOfSq (long n) ;
long sqOfSum (long n) ;

long main () {

	long difference = (sqOfSum(NUMBER) - sumOfSq(NUMBER));
	
	printf ("d: %li\n", difference); 
	

	return 0;

}

long sumOfSq (long n) {
	long i,sum = 0;
	for (i = 1; i <=n ;i++) sum = sum + (i*i);
	printf ("sumOfSq: %li\n",sum);
	return sum;

}

long sqOfSum (long n) {
	long i, sum = 0;
	for (i = 1; i <= n ; i++) sum = sum + i;
	printf ("sqOfSum: %li\n",sum*sum);
	return sum*sum;


}

