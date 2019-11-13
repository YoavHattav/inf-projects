#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mystrs.h"


size_t Mystrlen(const char *str)
{
	assert(NULL != str);
	const char *runner= str;
	while('\0' != *runner)
	{
		++runner;
	}
	return runner-str;
}


int Mystrcmp(const char *str_1, const char *str_2)
{
	assert(NULL != str_1);
	assert(NULL != str_2);
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

}
/*************** strcpy******/

void Mystrcpy(char *dest, char *sour)
{
	assert(NULL != dest);
	assert(NULL != sour);
    int i=0, leny=Mystrlen(sour);
	for (i=0 ; i<leny ; i++)
	{
		*dest= sour[i];
		++dest;
	}
}


/*************** strnnnnncpy******/

void Mystrncpy(char *dest, char *sour, int n)
{
	assert(NULL != dest);
	assert(NULL != sour);
    int i;
	for ( i=0 ; i<n ; i++ )
	{
		*dest= sour[i];
		++dest;
	}
}



/*************** strcasecmp ******/

int Mystrcasecmp(const char *a, const char *b)
{
	assert(NULL != a);
	assert(NULL != b);
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
    casecmpresult= Mystrcmp(lowera, lowerb);
    return casecmpresult;
}


/*************** strchries  ******/

char *Mystrchr(const char *chrstr, const char check)
{
    assert(NULL != chrstr);
    const char *runnerchr= chrstr;
    while (check != *runnerchr)
    {
        ++runnerchr;
    }
    return (char *)runnerchr;
}


/************** strdupies main ******/



char *Mystrdup(const char *sour_str)
{
	assert(NULL != sour_str);
    char *alocated_str = malloc((Mystrlen(sour_str)) * sizeof(char));
    char *duploc = alocated_str;
    while( '\0' != *sour_str)
    {
        *alocated_str = *sour_str;
        ++alocated_str;
        ++sour_str;
    }
    return duploc;
}

/************* dupies main  ************
 int main()
 {
     const char source_str[]="hey dude it is totally awesome to allocate memory!";
     char *duplocation=MyStrdup(source_str);
     printf("%s\n", duplocation);
     free(duplication);
     return 0;
 }
 ************** strdupies main ******/

char *Mystrcat(char *dest_cat, const char *sour_cat)
{
	assert(NULL != dest_cat);
	assert(NULL != sour_cat);
    char *runner=dest_cat;
    while('\0' != *dest_cat)
    {
        ++dest_cat;
    }
    while ('\0' != *sour_cat)
    {
        *dest_cat = *sour_cat;
        ++sour_cat;
        ++dest_cat;
    }
    return runner;
}


char *Mystrncat(char *dest_cat, const char *sour_cat, int n)
{
	assert(NULL != dest_cat);
	assert(NULL != sour_cat);
    char *runner=dest_cat;
    int i=0;
    while('\0' != *dest_cat)
    {
        ++dest_cat;
    }
    for(i=0;i<n;i++)
    {
        *dest_cat = *sour_cat;
        ++sour_cat;
        ++dest_cat;
    }
    return runner;
}

