#include <stdio.h>

float PowerHouse(int x)
{
int i;
float multi=10.0;
long double sum=1.0;
if (x<0)
{
	x*=(-1);
	multi=1/multi;
}
for (i=0;i<x;i++)
	sum*=multi;
return sum;
}
