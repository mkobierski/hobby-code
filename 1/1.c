#include <stdio.h>
#include <stdlib.h>

int main() {
	int i, c;
	c = 0;
	for (i = 1; i < 1000; i++) {
		if(i % 3 == 0 || i % 5 == 0) {
			c = c + i;
			printf ("num: %i\n",i);
		}
	}
	printf ("%i\n", c);



}
