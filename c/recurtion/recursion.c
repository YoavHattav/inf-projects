#include <stdio.h>
#include <time.h>

#include "recursion.h"
#include "../../ds/include/linked_list.h"

size_t FibIter(size_t n)
{
	size_t res = 1, prev = 1, result_holder = res;
	size_t i = 0;
	
	for (i = 1; i < n; ++i)
	{	
		result_holder = res;
		res += prev;
		prev = result_holder;
	}

	return res;
}

size_t FibRec(size_t n)
{
	if (2 > n)
		return 1;
	return (FibRec(n-1)+FibRec(n-2));
}

size_t StrlenRec(char *str)
{
	if ('\0' == *str)
		return 0;
	return StrlenRec(str + 1) + 1;
}

int StrcmpRec(const char *str1, const char *str2)
{
	if (*str1 != *str2 || *str1 == '\0' || *str2 == '\0')
	{
		return (*str1 - *str2);
	}
	return StrcmpRec(str1 + 1, str2 + 1);
}

char *StrcpyRec(char *dest, const char *src)
{
	if (*src != '\0')
	{
		StrcpyRec((dest + 1),(src + 1));
	}

	*dest = *src;

	return dest;
}

char *StrcatRec(char *dest, const char *src)
{
	if (*dest != '\0')
	{
		StrcatRec(dest + 1 , src);
	}

	else if ((*dest = *src) != '\0')
	{
		StrcatRec(dest + 1 , src + 1);
	}

	return dest;
}

char *StrstrRec(char *haystack, char *needle)
{
	if ( 0 == StrcmpRec(haystack, needle))
	{
		return haystack;
	}

	return StrstrRec(haystack + 1, needle);
}





