#include <string.h>
#include <stdio.h>
#include "IsRotate.h"

void Test(int cond, const char *massage)
{
	if (1 == cond)
	{
		printf("\033[1;32m""SUCC-%s\n", massage);
	}
	else
	{
		printf("\033[0;31m""FAIL-%s\n", massage );
	}
}

int main()
{	
	/*  int result = 0;

	const char *s1[5]={"hello"};
	char *s2[5];    */

	Test(IsRotatefinal("121234", "123412") == 1, "simple true");
	
	Test(IsRotatefinal("12345", "45123") == 1, "simple true");

	Test(IsRotatefinal("123", "1") == 0, "different sizes");

	Test(IsRotatefinal("123124125", "251231241") == 1, "hard true, im sry");

	Test(IsRotatefinal("yantiparazi", "raziyantipa") == 1, "hard trueth, im sry");


	return 0;
}