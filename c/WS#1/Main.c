#include <stdio.h>
#include "PowerHouse.c"
#include "FlipIt.c"
#include "SwapIt.c"

void main()
{

/*************************** SwapIt -ex6*/
int x, y;
int *xp, *yp;
printf("enter num1\n");
scanf("%d", &x);
printf("enter num2\n");
scanf("%d", &y);
xp=&x;
yp=&y;
SwapIt(xp, yp);
printf("num1 is now %d and num2 is now %d\n", x, y);

/********************* FlipIt initiation-  ex5 
	int num, renum;
	printf("enter num to be fliped: \n");
	scanf("%d", &num);
	renum=FlipIt(num);
	printf("the fliped num is: %d\n", renum);
*********************************************/

/******************* powerhouse initiation-ex4
long double result;
int N;			
scanf("%d", &N);
result=PowerHouse(N);
printf("%Lf\n", result);
**********************************************/

}
