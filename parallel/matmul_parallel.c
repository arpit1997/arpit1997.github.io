#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define N 500
#define NUM_THREADS 4

int A[N][N] ;
 
int B[N][N] ;

int C[N][N]; // To store result
int i, j;


struct v {
   int i; /* row */
   int j; /* column */
};

void *runner(void *param); /* the thread */

int main(int argc, char *argv[]) {
   for (i = 0; i < N; ++i)
{
  for (j = 0; j < N; ++j)
  {
      A[i][j] = i+j; 
  }
}
for (i = 0; i < N; ++i)
{
  for (j = 0; j < N; ++j)
  {
      B[i][j] = 2*i+j; 
  }
}

   int i,j, count = 0;
   for(i = 0; i < N; i++) {
      for(j = 0; j < N; j++) {
         //Assign a row and column for each thread
         struct v *data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         /* Now create the thread passing it data as a parameter */
         pthread_t tid;       //Thread ID
         pthread_attr_t attr; //Set of thread attributes
         //Get the default attributes
         pthread_attr_init(&attr);
         //Create the thread
         pthread_create(&tid,&attr,runner,data);
         //Make sure the parent waits for all thread to complete
         pthread_join(tid, NULL);
         count++;
      }
   }

   //Print out the resulting matrix
   for(i = 0; i < N; i++) {
      for(j = 0; j < N; j++) {
         printf("%d ", C[i][j]);
      }
      printf("\n");
   }
}

//The thread will begin control in this function
void *runner(void *param) {
   struct v *data = param; // the structure that holds our data
   int n, sum = 0; //the counter and sum

   //Row multiplied by column
   for(n = 0; n< N; n++){
      sum += A[data->i][n] * B[n][data->j];
   }
   //assign the sum to its coordinate
   C[data->i][data->j] = sum;

   //Exit the thread
   pthread_exit(0);
}