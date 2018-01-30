
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int nthreads, tid;

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nthreads, tid) num_threads(4)
  {

  /* Obtain thread number */
  tid = omp_get_thread_num();
  
   
   switch(tid){
    case 0: sleep(10);
    break;
    case 1: sleep(5);
    break;
    case 2: sleep(20);
    break;
    case 3: sleep(30);
    break;
   }
   printf("Hello World from thread = %d\n", tid);

  /* Only master thread does this */
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  }  /* All threads join master thread and disband */

}

