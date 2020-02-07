// test memory access time by "touching" elements of a linear array A
// with a progressively growing stepsize (stride).
//
// Author : Yuhua Ma (ym474)
// Date : 2/1/2020
// How to compile :
//
// % cd _sourcefile's path_
// % gcc -o benchmark benchmark.c
//
// no std=c99 because clock_gettime()
// add -pthread because pthread_create,pthread_join
// % ./benchmark
//
// #include <math.h> //pow()
#include <stdio.h>  //printf
#include <stdlib.h> // malloc
#include <time.h>   /* for clock_gettime */
#include <stdint.h> /* for uint64 definition */

#define BILLION 1E9L
#define MAX_LENGTH1 1 << 26
#define MIN_SIZE1 1 << 10

void main() {
  struct timespec start, end;
  double diff;
  float *A = (float *)malloc(sizeof(float) * MAX_LENGTH1); // whether init A[][]
                                                           // does not influence
                                                           // the experiment
                                                           // result

  int n, s, i, c, cnt = 10, tmp, j;

  FILE *f = fopen("problem1_data.txt", "w");

  for (n = MIN_SIZE1; n <= MAX_LENGTH1; n *= 2) {
    fprintf(f, "n = %ld\n", n);
    for (s = 1; s <= n / 2; s *= 2) {
      clock_gettime(CLOCK_MONOTONIC, &start);
      for (c = 0; c < cnt * s; c++) {
        for (i = 0; i < n; i += s) {
          tmp = A[i]; // load A[i]
        }
      }
      clock_gettime(CLOCK_MONOTONIC, &end);
      diff =
          BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
      diff = diff / (n * cnt);
      printf("array length(n) : %ld stride length(s) : %ld for s*n times. "
             "Average timing(sec) %llu\n",
             n, s, diff);
      fprintf(f, "%lf\n", diff);
    }
    fprintf(f, "------------------\n");
  }
  fclose(f);
}