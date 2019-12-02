#include <stdio.h>
#include <string.h>
#include "IsRotate.h"

int IsRotatefinal(const char *s1, const char *s2)
{
	int len = 0, n = 0;
	const char *s1run = s1, *s2run = s2;
	
	len = strlen(s2);
	n = len;

	if ( strlen(s2) != strlen(s1))
	{
		return false;
	}

		if(0 == strncmp(s1run, s2run, n))
		{	
			return true;
		}
		while ( '\0' != *s2run)
		{
			++s2run;
			--n;

			if(0 == strncmp(s1run, s2run, n))
			{	
				s2run = s2;
				s1run = s1+n;
				if (0 == strncmp(s1run, s2run, len-n))
				{
					return true;
				}
			}
		}
	return false;	
}

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