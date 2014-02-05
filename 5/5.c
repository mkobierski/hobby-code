#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MULTIPLE 20

int isDiv (int n);

int main () {

	int i;
	for (i = 1; !isDiv(i); i++);

	return 0;

}

int isDiv (int n) {
	int i;
	for (i = 1; i <= MULTIPLE; i++) 
		if(n % i != 0) 
			return 0;
		
	printf ("%i\n", n);
	return 1;
	


}
