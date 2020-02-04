/********************************/
/*	Yoav Hattav                 */
/*	24.11.19                    */
/*	AtoI / ItoA                 */
/*                              */
/*	Reviewer: Ben               */
/********************************/

#include <stdio.h> 
#include <string.h>

#define ZERO 48
#define A_IN_ASCII 55


int MyAtoIAnyBase(const char *str, int base)
{
    int convertion_res = 0, sign = 0;

    if ('-' == *str)
    {
        ++str;
        sign = 1;
    }

    while (*(str) != '\0')
    {
        convertion_res += (int)*str;
        printf("%d\n", convertion_res);
        if ( 9+ZERO >= (int)*str) 
        {
            convertion_res -= ZERO;
        }
        else if ( 9+ZERO <= (int)*str) 
        {
            convertion_res -= A_IN_ASCII;
        }
        ++str;
        if (1 == strlen(str))
        {
        	 convertion_res *= base;
        }
    }
    if (1 == sign)
    {
        return -convertion_res;
    }

    return convertion_res;
}

void StringVerse(char *str)
{
	char *runstart = str;
	char *runend = str + strlen(str) -1;
	int swapaid = 0;
	
	while (runstart < runend)
	{
		swapaid = *runend;
		*runend = *runstart;
		*runstart = swapaid;
		++runstart;
		--runend;
	}
}

char *MyItoaAnyBase(int num, char* stri2a, int base)
{
	int negflag = 0;
	char* str = stri2a;

	if (0 > num)
	{
		negflag = 1;
		num *= -1;
	}
	if (0 == num)
	{
		*str = 48;
		*(str+1) = '\0';
		return str;
	}
	while (0 != num)
	{
		int modul = num%base;
		if (9 < modul)
		{
			*str = modul + 55;
			++str;
			num /= base;
		}
		else 
		{
			*str = modul + 48;
			++str;
			num /= base;
		}
	}
	if (1 == negflag)
	{
		*str = '-';
	}
	StringVerse(stri2a);

	return stri2a;
}


int main() 
{ 
	/* ATOI Test */
    char stratoi[] = "10"; 
    int atoi = 0;
    /* ITOA Test */
    int itoa = 00202;
    char stritoa[30] = {0};
    int base = 2;

    atoi = MyAtoI(stratoi, base); 
    printf("%d\n", atoi);

    /*printf("%s\n", MyItoa(itoa, stritoa, base));*/

    return 0; 
} 
