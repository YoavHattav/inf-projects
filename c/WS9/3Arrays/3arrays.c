/********************************/
/*	Yoav Hattav                 */
/*	24.11.19                    */
/*	3Arrays                     */
/*                              */
/*	Reviewer: Ben               */
/********************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 40

void PrintTwoOfThree(char *arr1, char *arr2, char *arr3)
{
	char *print_arr = (char*)malloc(MAX);

	while ('\0' != *arr1)
	{
		if ((NULL != strchr(arr2, (int)*arr1)) && (NULL == strchr(arr3, (int)*arr1)) 
		 && (NULL == strchr(print_arr, (int)*arr1)))
		{
			*print_arr = *arr1;
			printf("%c\n", *arr1);
		}
		++arr1;
	}
	
	free(print_arr);
}

int main()
{
	char arr1[MAX] = "11122229";
	char arr2[MAX] = "1234567";
	char arr3[MAX] = "8748762398472";

	PrintTwoOfThree(arr1, arr2, arr3);

	return 0;
}