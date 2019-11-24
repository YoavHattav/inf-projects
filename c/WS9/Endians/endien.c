#include <stdio.h>

#define END(x) ((*(char*)&x) == 1) ? printf("Biggy\n") : printf("Smalls\n");


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
	int x = 1;
	int num = 0x00001111;
	BiggySmalls((char*)&num);

	END(x);

	return 0;
}