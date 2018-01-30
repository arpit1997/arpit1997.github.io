#include<stdio.h>
int calc(int n){
	int x;
	if (n==1)
	{
		return 1;
	}else if(n==0){
		return 0;
	}
	else 
	x= (calc(n-1)+calc(n-2));
	if (x%2==0)
	{
		even();
	}
	display(x);
}

int display(int n){
	printf("%d\n",n );
}

int even(){

}

int main(int argc, char const *argv[])
{
	int a=6;

	return 0;
}