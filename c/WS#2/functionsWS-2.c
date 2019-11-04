#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

/*********** strlen with assert ***
size_t strlenie(const char *str)
{
	
	assert(NULL != str);
	const char *runner= str;
	while('\0' != *runner)
	{
		++runner;
	}
	return runner-str;
}
***********************************/


/*************** strlen ******/

size_t Strlenie(const char *str)
{
	/***********assert*******/
	const char *runner= str;
	while('\0' != *runner)
	{
		++runner;
	}
	return runner-str;
}


/*********** strcmp ***/

int Strcmpie(const char *str_1, const char *str_2)
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

}
/*************** strcmp main******
int main()
{
	int cmpresult=0;
	const char a[] = "aaaaaaa";
	const char b[] = "aaaA";
	cmpresult= strcmpie(a, b);
	printf("the comparison's value after cmp is: %d\n", cmpresult);
	return 0;
}
*************** strcmp main******/



/*************** strcpy******/

void Strcpyeis(char *dest, char *sour)
{
    int i, leny;
	leny= strlenie(sour);
	for (i=0 ; i<leny ; i++)
	{
		*dest= sour[i];
		++dest;
	}
}
/*************** strcpy main ******
 int main()
{
    char a[50]="hey you", b[50]="come here";
    strcpyeis(a, b);
    printf("%s", a);
    
}
*************** strcpy main ******/




/*************** strnnnnncpy******/

void Strncpyeis(char *dest, char *sour, int n)
{
    int i;
	for ( i=0 ; i<n ; i++ )
	{
		*dest= sour[i];
		++dest;
	}
}
/*************** strncpy main******
 int main()
{
    char a[50]="hey you", b[50]="come here";
    int number_of_times=3;
    Strncpyeis(a, b, number_of_times);
    printf("%s\n", a);
}
*************** strncpy main******/




/*************** strcasecmp ******/

int Strcasecmpies(const char *a, const char *b)
{
    char lowera[50], lowerb[50];
    int casecmpresult=0, i=0;
    while('\0' != *a )
    {
        lowera[i]=*a;
        ++a;
        lowera[i]= tolower(lowera[i]);
        ++i;
    }
    i=0;
    while('\0' != *b )
    {
        lowerb[i]=*b;
        ++b;
        lowerb[i]= tolower(lowerb[i]);
        ++i;
    }
    casecmpresult= Strcmpie(lowera, lowerb);
    return casecmpresult;
}
/*************** strcasecmp main ******

 int main()
{
    const char Y[50]="heyyoUh", H[50]="heYyouHYty";
    int caseresult=0;
    caseresult = Strcasecmpies(Y, H);
    if(0 == caseresult)
    {
        printf("the strings are equal");
    }
    else if (0 < caseresult)
    {
        printf("the Y string is more than H");
    }
    else
    {
        printf("the H string is more than Y");
    }
}
*************** strcasecmp main ******/