#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int isPalindrome (int p);

int main () {

	int i;
	
	int a, b, largest;
	
	for (a = 999, b = 999, largest = 0; a > 99 && b > 99;) {
		printf ("a : %i, b : %i\n",a,b);
		if( b == 100 ) {
			a--;
			b = 999;
		}
		if (isPalindrome(a * b) && (a*b) > largest) largest = a*b;
		b--;

	}
	printf ("%i\n", largest);


	return 0;

}

int isPalindrome (int p) {
	char w[7];
	sprintf(w,"%d",p);
	int i, l, u;
	for (i = 0; i < 7 ; i++)
		if(w[i] == '\0') break;
	if(i != 0) {
		l = 0;
		u = i-1;


		if( u % 2 == 1 ) { //even
			do {
				if (w[l] == w[u]) {
					l++;
					u--;
				} else return 0;

			} while (u > l);
			if( u == (l - 1)) return 1;
		} else { //odd
			while ( u == (l + 2)) {
				if(w[l] == w[u]) {
					l++;
					u--;
				} else return 0;
			}
			if (u == l) return 1;
		}
		

	}
	return 0;
}
