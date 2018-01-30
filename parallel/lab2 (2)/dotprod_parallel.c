/******************************************************************************
* FILE: dotprod.c
* DESCRIPTION:
*   This is a simple serial program which computes the dot product of two 
*   vectors.  The threaded version can is dotprod_mutex.c.
* SOURCE: Vijay Sonnad, IBM
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*   
The following structure contains the necessary information  
to allow the function "dotprod" to access its input data and 
place its output so that it can be accessed later. 
*/
int per_thread;
typedef struct 
{
  double      *a;
  double      *b;
  double     sum; 
  int    veclen; 
} DOTDATA;
int NUM_THREADS= 8;
#define VECLEN 100000000
  DOTDATA dotstr; 

pthread_mutex_t sum_mutex;
/*
We will use a function (dotprod) to perform the scalar product. 
All input to this routine is obtained through a structure of 
type DOTDATA and all output from this function is written into
this same structure.  While this is unnecessarily restrictive 
for a sequential program, it will turn out to be useful when
we modify the program to compute in parallel.
*/

void* dotprod(void* n)
{

/* Define and use local variables for convenience */

   int start, end,temp_sum;
   int* i_a = (int *) n;
   int i = *i_a;
   double *x, *y;
   start=i*per_thread;
   end = start+per_thread;
   if(end > VECLEN){
   		end =VECLEN;
   }
   x = dotstr.a;
   y = dotstr.b;

/*
Perform the dot product and assign result
to the appropriate variable in the structure. 
*/

   for (i=start; i<end ; i++) 
    {
	  temp_sum += (x[i] * y[i]);
    }
    pthread_mutex_lock(&sum_mutex);
	dotstr.sum += temp_sum;
    pthread_mutex_unlock(&sum_mutex);
}

/*
The main program initializes data and calls the dotprd() function.
Finally, it prints the result.
*/

int main (int argc, char *argv[]){
	// int o
	if(argc!=0)
        NUM_THREADS = atoi(argv[1]);
	int i,len;
	double *a, *b;
	   
	/* Assign storage and initialize values */
	len = VECLEN;
	a = (double*) malloc (len*sizeof(double));
	b = (double*) malloc (len*sizeof(double));
	 
	for (i=0; i<len; i++) {
	  a[i]=1;
	  b[i]=a[i];
	  }

	dotstr.veclen = len; 
	dotstr.a = a; 
	dotstr.b = b; 
	dotstr.sum=0;

	/* Perform the  dotproduct */
	// per_thread = len/NUM_THREADS;
	per_thread = len%NUM_THREADS == 0? len/NUM_THREADS:len/NUM_THREADS+1;

	pthread_t *threads = (pthread_t*)calloc(NUM_THREADS, sizeof(pthread_t));
	for (i = 0; i < NUM_THREADS; ++i)
	{
		pthread_create(&threads[i], NULL, dotprod, (void *)&i);
	}
	for(i=0; i<NUM_THREADS; i++) {
        //join each thread after each thread complete work
        pthread_join(threads[i], NULL);
    }

	// dotstr.sum = mysum;

	/* Print result and release storage */ 
	printf ("Sum =  %f \n", dotstr.sum);
	free (a);
	free (b);
}