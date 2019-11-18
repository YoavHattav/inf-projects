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