#include <stdio.h>
#define N 800
 
// This function multiplies A[][] and B[][], and stores
// the result in C[][]
void multiply(int A[][N], int B[][N], int C[][N])
{
    int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < N; k++)
                C[i][j] += A[i][k]*B[k][j];
        }
    }
}
 
int main()
{
    int A[N][N] ;
 
    int B[N][N] ;
 
    int C[N][N]; // To store result
    int i, j;
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
    
    multiply(A, B, C);
    printf("Result matrix is \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        	continue;
          // printf("%d ", C[i][j]);
        // printf("\n");
    }
 
    return 0;
}
