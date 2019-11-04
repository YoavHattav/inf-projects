#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mystrs.h"


size_t Strlenies(const char *str)
{
	/***********assert*******/
	const char *runner= str;
	while('\0' != *runner)
	{
		++runner;
	}
	return runner-str;
}


int Strcmpies(const char *str_1, const char *str_2)
{
	int result=0;
	while( '\0' != *str_1  ||  '\0' != *str_2 )
	{
		if(*str_1 != *str_2)
		{
			result = (*str_1 - *str_2);
			break;
		}
		++str_1;
		++str_2;
	}

	return result;

}/*************** strcpy******/

void Strcpyies(char *dest, char *sour)
{
    int i, leny;
	leny= strlenies(sour);
	for (i=0 ; i<leny ; i++)
	{
		*dest= sour[i];
		++dest;
	}
}


/*************** strnnnnncpy******/

void Strncpyies(char *dest, char *sour, int n)
{
    int i;
	for ( i=0 ; i<n ; i++ )
	{
		*dest= sour[i];
		++dest;
	}
}



/*************** strcasecmp ******/

int Strcasecmpies(const char *a, const char *b)
{
    char lowera[50], lowerb[50];
    int casecmpresult=0, i=0;
    while( '\0' != *a )
    {
        lowera[i] = *a;
        ++a;
        lowera[i] = tolower(lowera[i]);
        ++i;
    }
    i=0;
    while( '\0' != *b )
    {
        lowerb[i] = *b;
        ++b;
        lowerb[i] = tolower(lowerb[i]);
        ++i;
    }
    casecmpresult= Strcmpies(lowera, lowerb);
    return casecmpresult;
}


/*************** strchries  ******/

char *strchries(const char *chrstr, const char check)
{
    while (check != *chrstr)
    {
        ++chrstr;
    }
    return chrstr;
}


/************** strdupies main ******/

/******* "free needs fixing!!!!!!!!"********

char *Strdupies(const char *sour_str)
{
    char *alocated_str= malloc((Strlenies(sour_str)) * sizeof(char));
    char *duploc=alocated_str;
    while( '\0' != *sour_str)
    {
        *alocated_str=*sour_str;
        ++alocated_str;
        ++sour_str;
    }
    return duploc;
}


 int main()
 {
     const char source_str[]="hey dude this is totally awesome to allocate memory!";
     char *duplocation=Strdupies(source_str);
     printf("%s\n", duplocation);
     free(alocated_str);
     return 0;
 }
 ************** strdupies main ******/
