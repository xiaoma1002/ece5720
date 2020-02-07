// a "tiled" matrix-matrix multiplication
//
// Author : Yuhua Ma (ym474)
// Date : 1/30/2020
//
// % cd _sourcefile's path_
// % gcc -o tile ym474_mm_tile.c
// % ./tile _dim_n's value_ _tile's value_
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
tile multiplication
time consumption
*/
int main(int argc, char *argv[])
{
	// create matrix A,B,C using malloc
	if (argc != 3)
	{
		printf("wrong number of input arguments\n");
	}

	int dim_n = atoi(argv[1]);
	int tile_size = atoi(argv[2]);
	int p = dim_n / tile_size;
	printf("dim_n = %d\n", dim_n);
	printf("tile_size = %d\n", tile_size);
	printf("p = %d\n", p);

	int* A= (int *)malloc(dim_n * dim_n * sizeof(int));;
	int* B= (int *)malloc(dim_n * dim_n * sizeof(int));;
	int* C = (int *)malloc(dim_n * dim_n * sizeof(int));
	
	// fill-in matrix A, B
	double drand48();
	void srand48();
	srand48(1);
	int i,j;
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
	// define I, J, K for block's index
	// define i_,j_,k_ for index of a block
	// define i,j,k for real index
	int I, J, K,k ,i_,j_,k_;
	for(I = 0; I < p; I++){
		for(J = 0;J < p; J++){
			for(K = 0; K < p; K++){
				for(i_ = 0; i_ < tile_size; i_++){
					for(j_ = 0; j_ < tile_size; j_++){
						for(k_ = 0; k_ < tile_size; k_++){
							i = tile_size * I + i_;
							j = tile_size * J + j_;
							k = tile_size * K + k_;

							*(C + i*dim_n + j) = *(C + i*dim_n + j) + (*(A + i*dim_n + k) * *(A + k*dim_n + j));	

						}
					}
				}


			}
		}
	}

	clock_gettime(CLOCK_MONOTONIC,&end);
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("timing(nsec) %lf\n", diff);

	return 0;
}