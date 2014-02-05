#include <stdlib.h>
#include <stdio.h>

int isPyTrip (int a, int b, int c);


int main () {

	int a = 3;
	int b = 4;
	int c = 5;
	

	for (a = 3; a < 1000;a++)
		for(b = a+1; b < 1000; b++)
			for(c = b+1; c < 1000; c++)
				if(isPyTrip(a,b,c) && (a + b + c == 1000)) printf ("a = %i\nb = %i\nc = %i\nabc = %i\n",a,b,c,a*b*c);
	


	return 0;
}

int isPyTrip (int a, int b, int c) {

	if( a*a + b*b == c*c ) return 1;
	return 0;

}
