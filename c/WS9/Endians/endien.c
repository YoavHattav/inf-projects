/********************************/
/*	Yoav Hattav                 */
/*	24.11.19                    */
/*	AtoI / ItoA                 */
/*                              */
/*	Reviewer: Ben               */
/********************************/
#include <stdio.h>

#define END(x) ((*(char*)&x) == (x & 0xff)) ? printf("Smalls\n") : printf("Biggy\n");


void BiggySmalls(char *integ)
{
	if (0 == *integ)
	{
		printf("Biggy\n");
	}
	else
	{
		printf("Smalls\n");
	}
}

int main()
{
	int x = 1025;
	int num = 0x0f;
	
	BiggySmalls((char*)&num);

	END(x);

	return 0;
}