#include <stdio.h>
#include <stdlib.h>

int main () {
	int f1 = 1;
	int f2 = 1;
	int f3 = 2;
	int sum = 0;
	while (f1 <= 4000000 && f2 <= 4000000) {
		if(f3 % 2 == 0){
			sum = sum + f3;
			printf ("f3 : %i\nsum: %i\n", f3, sum);
		}
		f1 = f2;
		f2 = f3;
		f3 = f1 + f2;

	}
	printf ("%i\n", sum);

}
