#include <stdlib.h>
#include <stdio.h>

#define OFFSET 48

int main () {

	FILE *fp;
	fp = fopen("seq.txt", "r");

	char cp[2];

	int a,b,c,d,e;
	int prod = 0, maxProd = 0;
	

	if(fp == NULL) {
		fprintf(stderr, "Can't open input file in.list!\n");
	} else {
		b=fgetc(fp) - OFFSET;
		c=fgetc(fp) - OFFSET;
		d=fgetc(fp) - OFFSET;
		e=fgetc(fp) - OFFSET;
	
		
		do  {	
			a = b;
			b = c;
			c = d;
			d = e;
			e = fgetc(fp) - OFFSET;
			
			prod = a*b*c*d*e;

			if (prod > maxProd) maxProd = prod;

		} while (!feof(fp));
		printf ("maxProd : %i", maxProd);


		fclose(fp);
	}
	

	return 0;
}

