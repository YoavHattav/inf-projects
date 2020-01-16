#include <stdio.h>
#include <string.h>
#include <time.h>

#include "recursion.h"

void TestFibItr()
{
	size_t result = 0;
	size_t n = 50;
	clock_t start = 0, end = 0;

	start = clock();
	result = FibIter(n);
	end = clock();
	printf("%lu\n", result);
	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);
}

void TestFibRec()
{
	size_t result = 0;
	size_t n = 50;
	clock_t start = 0, end = 0;

	start = clock();
	result = FibRec(n);
	end = clock();	
	printf("%lu\n", result);
	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);
}

void TestStrlenRec()
{
	printf("*****strlen*****\n");

	printf("%lu\n", StrlenRec("live life above all reason"));
	printf("%lu\n", StrlenRec("21 21 21 21"));

}

void TestStrcmpRec()
{
	printf("*****strcmp*****\n");

	printf("%d\n", StrcmpRec("ya cant stand right here", "ya cant stand right here")); 
	printf("%d\n", StrcmpRec("ya cant stand right here", "ya cant stand right here!"));
	printf("%d\n", StrcmpRec("ya cant stand right here! ", "ya cant stand right here!")); 
 

}

void TestStrcpyRec()
{
	char src[27] = {"live life above all reason"};
	char dest[100] = {"yonatan akatan ratz baboker el"};

	printf("*****strcpy*****\n");

	printf("%s\n", StrcpyRec(dest, src));
}

void TestStrcatRec()
{
	char src[27] = {"2 BG"};
	char dest[100] = {"we'll be OG "};
	char src2[27] = {"2 BG"};
	char dest2[100] = {"we'll be OG "};

	printf("*****strcat*****\n");

	printf("%s\n", StrcatRec(dest, src));
	printf("%s\n", strcat(dest2, src2));

}

void TestStrstrRec()
{
	char src[27] = {"2 BG"};
	char dest[100] = {"we'll be OG 2 BG"};
	char *ret = NULL;
	

	printf("*****strstr*****\n");

	ret = StrstrRec(src, dest);
	
	if (NULL != ret)
	{
		printf("%s\n", ret);		
	}
}

int main()
{
	
	/*TestFibRec();*/
	TestFibItr();
	TestStrlenRec();
	TestStrcmpRec();
	TestStrcpyRec();
	TestStrcatRec();
	TestStrstrRec();


	return 0;
}