#include <stdio.h>
#include "bitwisefuncs.h"


long Pow2(unsigned int x, unsigned int y)
{
	return x<<y;
}
enum status IsItpow2(unsigned n)
{
	int i = 0;
	long res = 2;
	for (i = 0 ; i < n ; i ++)
	{
		if ( res<<i == n )
		{
			return true;
		}
	}
	return false;
}
enum status IsItpow2p2(unsigned n)
{
	if ( 0 == (n & (n-1)))
	{
		return true;
	}
	return false;
}
