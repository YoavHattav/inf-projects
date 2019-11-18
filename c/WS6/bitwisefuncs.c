/********************************/
/*	Yoav Hattav                 */
/*	13.11.19                    */
/*	Files and strings           */
/*                              */
/*	Reviewer: Raz the slayer    */
/********************************/
#include <stdio.h>
#include "bitwisefuncs.h"


long Pow2(unsigned int x, unsigned int y)
{
	return x << y;
}

enum status IsItpow2(unsigned n)
{
	unsigned int i = 0;
	long res = 2;
	for (i = 0 ; i < n ; i ++)
	{
		if ( res << i == n )
		{
			return TRUE;
		}
	}
	return FALSE;
}

enum status IsItpow2p2(unsigned n)
{
	if ( 0 == (n & (n-1)))
	{
		return TRUE;
	}
	return FALSE;
}

int AddOne(int a)
{
	int ope = 1;

	while ( a & ope )
	{
		a = a ^ ope;
		ope = ope << 1;
	}

	a = a ^ ope;
	return a; 
}

void ThreeOn(unsigned int *arr)
{
	unsigned int n = 0; 
	int counter = 0;
	int i = 0;

	for ( ; i < MAX ; i++ )
	{
		n = *arr;
		counter = 0;
		while ( n )
		{
			counter = counter + (n & 1);
			n >>= 1;
		}

		if ( 3 == counter )
		{
			printf("%u\n", *arr);
		}

		++arr;
	}
}

int HowManySet(int n)
{
	int counter = 0;

	while ( n )
	{
		counter = counter + (n & 1);
		n >>= 1;
	}
	return counter;
}

unsigned int ByteMirror(unsigned int x)
{
	int m = 1;
	unsigned int mirror = 0;
	unsigned int temp = 0;
	int i = 0;

	for ( i = 0; i < 32 ; i++)
	{
		mirror <<= 1;
		temp = x & m;
		mirror |= temp;
		x >>= 1;
	}

	return mirror;
}

unsigned char BothTwoAndSix(unsigned char x)
{
	return ( ( 1 & (x>>1)) && ( 1 & (x>>5)) );
}

unsigned char OneOfTwoAndSix(unsigned char x)
{
	return ( ( 1 & (x>>1)) || ( 1 & (x>>5)) );
}

unsigned char SwapThirdAndFifth(unsigned char x)
{
	unsigned char m3 = 0;
	unsigned char m5 = 0;
	unsigned char a = 0;

	m3 = (x >> 2) & 1;
	m5 = (x >> 4) & 1;
	a = m3 ^ m5;
	a = (a << 2) | (a << 4);

	return (x ^ a);
}

void Swap(unsigned int *a, unsigned int *b)
{
	printf("original value x:%u y:%u\n", *a, *b );
	*a = *a ^ *b;
	*b = *b ^ *a;
	*a = *a ^ *b;
}

void ShowBits(unsigned int n)
{
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
    {
      (n & i)? printf("1"): printf("0");
    }
    printf("\n");
}

unsigned int Closest(unsigned int x)
{
	return ((x >> 4) << 4); 
}

int SetBitCounterNoLoop(unsigned int x)
{

    if (0 == x)
    {
		return 0; 
    } 
    else
    {
        return (x & 1) + SetBitCounterNoLoop(x >> 1); 
    }
} 

unsigned int ByteMirrorNoLoop(unsigned int x)
{

	x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
	x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
	x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
	x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
	
	return((x >> 16) | (x << 16));
}

int Float_bit(int a, int loc)   
{
    int buf = a & 1<<loc;

    if (buf == 0)
    {
    	return 0;
    }
    else
    {
    	return 1; 
    }	
}

void Float_print(float a)
{
	int i;
    unsigned int *b;
    b = (unsigned int*)(&a);

    
    for (i = 31; i >= 0; i--)
    {
        printf("%d",Float_bit(*b, i));
    }
    printf("\n");
}

/* void Test(int cond, const char *massage)
{
	if (1 == cond)
	{
		printf("\033[1;32m""SUCC-%s\n", massage);
	}
	else
	{
		printf("\033[0;31m""FAIL-%s\n", massage );
	}
}  */


	