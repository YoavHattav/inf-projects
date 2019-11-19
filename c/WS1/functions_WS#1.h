#include <stdio.h>


/*************functions WS#1**************/

int FlipIt(int x)
{
	int temp=0, result=0, flag=0;
	if(x<0)
	{
	x = x * (-1);
	flag=1;
	}
	while(x>0)
	{
		temp = x % 10;
		x= x / 10;
		result= (result+temp) * 10;
	}
	result= result / 10;
	
	return (1==flag ? result * (-1) : result);
}
	
void SwapIt(int *a, int *b)
{
	int temp=0;
	temp= *a;
	*a= *b;
	*b= temp;
}


float PowerHouse(int x)
{
	int i;
	float multi=10.0;
	long double sum=1.0;
	if ( 0>x )
	{
		x *= (-1);
		multi = 1 / multi;
	}
	for ( i=0 ; i<x ; i++ ) 
		{
		sum*=multi;
		}
	return sum;
}
