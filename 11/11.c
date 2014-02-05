#include <stdlib.h>
#include <stdio.h>

int main () {

	FILE *fp;
	fp = fopen("grid.txt", "r");

	int grid [20][20];
	int i,j;

	if(fp == NULL) {
		fprintf(stderr, "Can't open input file grid.txt!\n");
	} else {	
		
			
		for(i = 0; i < 20; i++)
			for(j = 0; j < 20; j++)
				fscanf(	fp, "%2i", &(grid[j][i]));

		for(i = 0; i < 20; i++) {
			for(j = 0; j < 20; j++)
				printf ("%2i ", grid[j][i]);
			printf("\n");
		}
		



		fclose(fp);
	}
	

	return 0;
}

