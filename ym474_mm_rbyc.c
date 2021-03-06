// a simple "row-by-colum" matrix matrix multiplication
//
// Author : Yuhua Ma (ym474)
// Date : 1/30/2020
// How to compile :
//
// % cd _sourcefile's path_
// % gcc -o rbyc ym474_mm_rbyc.c
// % ./rbyc _dim_n's value_
//

#include <stdio.h> //printf
#include <stdlib.h> // malloc
#include <time.h> /* for clock_gettime */
#include <stdint.h>	/* for uint64 definition */

#define BILLION 1000000000L
void printMatrix(int *matrix, int row, int col);

void printMatrix(int *matrix, int row, int col)
{
	int i,j;
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){			
			printf("%d ",matrix[i*col+j]);
		}
		printf("\n");
	}
	printf("\n");
}


/*
createMatrix
rbyc multiplication
time consumption
*/
int main(int argc, char *argv[])
{
	// create matrix A,B,C using malloc
	if (argc != 2)
	{
		printf("wrong number of input arguments\n");
	}

	int dim_n = atoi(argv[1]);
	printf("dim_n = %d\n", dim_n);

	int* A= (int *)malloc(dim_n * dim_n * sizeof(int));;
	int* B= (int *)malloc(dim_n * dim_n * sizeof(int));;
	int* C = (int *)malloc(dim_n * dim_n * sizeof(int));
	
	// fill-in matrix A, B
	double drand48();
	void srand48();
	srand48(1);
	int i,j,k;
	for (i = 0; i < dim_n; i++)
	{
		for (j = 0; j < dim_n; j++)
		{
			*(A + i * dim_n + j) = (int)(drand48()*100);
			*(B + i * dim_n + j) = (int)(drand48()*100);
		}
	}	

    // calculate matrix C
    struct timespec start,end;
    double diff;
	clock_gettime(CLOCK_MONOTONIC,&start);
	for(i = 0; i < dim_n; i++){
		for(j = 0; j < dim_n; j++){
			for(k = 0; k < dim_n; k++){
				
				*(C + i*dim_n + j) = *(C + i*dim_n + j) + (*(A + i*dim_n + k) * *(A + k*dim_n + j));
			}
		}
	}
	
	clock_gettime(CLOCK_MONOTONIC,&end);
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("timing(nsec) %lf\n", diff);

	return 0;
}