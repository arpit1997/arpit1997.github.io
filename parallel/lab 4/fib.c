#include<stdio.h>

int fib(int x){
	int y;
	int i;
	int series[x];
	for ( i = 0; i < x; ++i)
	{
		y=calc(i);
		series[i]=y;
		if (y%2==0)
		{
			even();
		}
		
	}
	display(series,x);
		// sleep(1);
	return x+y;
}
int calc(int n){
	int x;
	if (n==1)
	{
		return 1;
	}else if(n==0){
		return 0;
	}
	else 
	x= calc(n-1)+calc(n-2);
	return x;
	//display(x);
}


int display(int* series,int size){
	int i=0;
	for (i = 0; i < size; ++i)
	{
		printf(" %d",series[i] );
	}
}

int even(){
	//printf("I am even\n" );

}

int main(int argc, char const *argv[])
{
	int a=25;
	// scanf("%d", &a);
	fib(a);
	printf("\n");
	return 0;
}