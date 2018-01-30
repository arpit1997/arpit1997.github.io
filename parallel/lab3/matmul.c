#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 500 
#define NCA 500 
#define NCB 000 

int main (int argc, char *argv[]) 
{
int tid, nthreads, i, j, k, chunk;
// double a[NRA][NCA], 
// b[NCA][NCB], 
// c[NRA][NCB]; 
double **a = (double **)malloc(NRA * sizeof(double *));
 for (i=0; i<NRA; i++)
 a[i] = (double *)malloc(NCA * sizeof(double));
double **b = (double **)malloc(NCA * sizeof(double *));
 for (i=0; i<NCB; i++)
 b[i] = (double *)malloc(NCB * sizeof(double));
double **c = (double **)malloc(NRA * sizeof(double *));
 for (i=0; i<NRA; i++)
 c[i] = (double *)malloc(NCB * sizeof(double));
// double *a = (double *)malloc(NRA*NCA*sizeof(double)); 
// double *b = (double *)malloc(NCA*NCB*sizeof(double)); 
// double *c = (double *)malloc(NRA*NCB*sizeof(double)); 

chunk = 10; 
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
 {
 tid = omp_get_thread_num();
 if (tid == 0)
 {
 nthreads = omp_get_num_threads();
 }
 printf("Hello world\n");
 for (i=0; i<NRA; i++)
 for (j=0; j<NCA; j++)
 a[i][j]= i+j;
 for (i=0; i<NCA; i++)
 for (j=0; j<NCB; j++)
 b[i][j]= i*j;
 for (i=0; i<NRA; i++)
 for (j=0; j<NCB; j++)
 c[i][j]= 0;

 //#pragma omp for schedule (dynamic, chunk)
 for (i=0; i<NRA; i++) 
 {
 printf("Thread=%d did row=%d\n",tid,i);
 for(j=0; j<NCB; j++) 
 for (k=0; k<NCA; k++)
 c[i][j] += a[i][k] * b[k][j];
 }
}
printf("Result Matrix:\n");
for (i=0; i<NRA; i++)
 {
 for (j=0; j<NCB; j++) 
 printf("%6.2f ", c[i][j]);
 printf("\n"); 
 }
}