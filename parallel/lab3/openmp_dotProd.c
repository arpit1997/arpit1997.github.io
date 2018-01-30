#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[]) 
{
int   i, n;
float a[100000], b[100000], sum; 

/* Some initializations */
n = 100000;
for (i=0; i < n; i++)
  a[i] = b[i] = i * 1.0;
sum = 0.0;
clock_t start = clock();
#pragma omp parallel for reduction(+:sum) num_threads(4)
  for (i=0; i < n; i++)
    sum = sum + (a[i] * b[i]);
clock_t end = clock();

printf("   Sum = %f\n",sum);
printf("   time = %f\n",(double)(end-start)/CLOCKS_PER_SEC);
}