#include <stdio.h>
#include <stdlib.h>
#include "LUT_of_funcs.h"

/********************************/
/*	Yoav Hattav			        */
/*	11.11.19		        	*/
/*	LUT of Fun       			*/
/*								*/
/*	Reviewer: Shye The Presser	*/
/********************************/

/* the function tells you when you pressed an invalid char */
int InWalid(char c)
{
	printf("Invalid fun char, Try again\n");

	return 1;
}

/* the function prints ur valid char */
int PrintIt(char ch)
{
	printf("%c was Pressed\n", ch);

	return 1;
}

/* the function exits he program */
int Terminate(char c)
{
	printf("Terminating program..\n");

	return 0;
}

/* the function makes use of the LUT i made */
int USELUT(int (*LUT[])(char))
{
	char ch=1;

	system("stty -icanon -echo");
	printf("enter keyboard input\n");

	do
	{
		ch=getchar();
	}while((*LUT[ch])(ch));

	system("stty icanon echo");
	
	return 1;
}

/* the function creats the LUT and enters valid functions into it */
int CreatLUT(int (*LUT[])(char))
{
	int i=0;
	
	for( ; i<256; i++)
	{
		LUT[i] = &InWalid;
	}

	LUT[65] = &PrintIt;
	LUT[84] = &PrintIt;
	LUT[27] = &Terminate;

	return 1;
}


