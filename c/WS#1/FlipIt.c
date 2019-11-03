#include <stdio.h>

int FlipIt(int x)
{
	int temp=0, result=0, flag=0;
	if(x<0)
	{
	x=x*(-1);
	flag=1;
	}
	while(x>0)
	{
		temp=x%10;
		x=x/10;
		result= (result+temp)*10;
	}
	result=result/10;
	
	return (flag==1 ? result*(-1) : result);
}	
