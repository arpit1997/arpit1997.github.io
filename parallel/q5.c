#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> 

#define N 500
int NUM_THREADS = 4;
long long count;

long int mat1[N][N], mat2[N][N], mat3[N][N];
long per_thread = 0;
pthread_t *threads;
// pthread_t threads[NUM_THREADS];

void *thread_Multiply_Matrix(void *);

void printMat(long int m[N][N], int r, int c){
    int i, j;
    for(i = 0; i< r; i++){
        for(j = 0; j< c; j++)
        {
            printf("%ld  ", m[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{  
    if(argc!=0)
        NUM_THREADS = atoi(argv[1]);
    printf("Working with %d threads\n", NUM_THREADS);
    int i,j,k;
    void *status;
    printf("Rows and Columns of Matrix 1: %d x %d\n", N, N);
   for (i = 0; i < N; ++i)
{
  for (j = 0; j < N; ++j)
  {
      mat1[i][j] = i+j; 
  }
}

    printf("Matrix 1 initialized\n");

    printf("Rows and Columns of Matrix 2: %d x %d\n", N, N);
for (i = 0; i < N; ++i)
{
  for (j = 0; j < N; ++j)
  {
      mat2[i][j] = 2*i+j; 
  }
}

    printf("Matrix 2 initialized\n");
    // number of rows devided equally between all threads  
    per_thread = N/NUM_THREADS;
    // allpt memory for each thread
    pthread_t *threads = (pthread_t*)calloc(NUM_THREADS, sizeof(pthread_t));
    for(i = 0; i< NUM_THREADS; i++)
    {
        //create each thread
        pthread_create(&threads[i], NULL, thread_Multiply_Matrix, (void *)i);
    }
    int rc;
    for(i=0; i<NUM_THREADS; i++) {
        //join each thread after each thread complete work
        rc = pthread_join(threads[i], &status);
    }

    printf("\nMatrix Multiplication Complete\n");
}

void *thread_Multiply_Matrix(void *tid)
{

    int id = (int)tid;  
    int i,j,k;
    int sum = 0;
    int start = id*per_thread;
    int end = start + per_thread;
    
    for(i = start; i<end; i++)
    {
        for(k = 0; k<N; k++)
        {
            sum = 0;
            for(j = 0; j<N; j++){
                sum = sum + mat1[i][j]*mat2[j][k];
            }
            mat3[i][k] = sum;
        }

    }
    pthread_exit(NULL);
    
}