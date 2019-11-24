#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 40
void PrintTwoOfThree(char *arr1, char *arr2, char *arr3)
{
	
	while ('\0' != *arr1)
	{
		if ((NULL != strchr(arr2, (int)*arr1)) && (NULL == strchr(arr3, (int)*arr1)))
		{
			printf("%c\n", *arr1);
		}
		++arr1;
	}
	printf("%s\n", arr1);
}

int main()
{
	char arr1[MAX] = "ASDFGHJKL";
	char arr2[MAX] = "ADGJdfghdgfhL";
	char arr3[MAX] = "8748762398472";

	PrintTwoOfThree(arr1, arr2, arr3);

	return 0;
}