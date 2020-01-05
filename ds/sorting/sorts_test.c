/*********************************/
/*    Data Structures            */
/*    sorts                      */
/*    Author : Yoav Hattav       */
/*    Reviewed By:               */
/*    Date:      05/01/2020      */
/*                               */
/*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorts.h"

#define SIZE_OF_ARR 100000

void ArrayFiller(int *arr)
{
	int i = 0;
	srand(time(0));
	for (i = SIZE_OF_ARR;i > 0;i--)
	{
		*arr = ((rand()%20 )-10);
		++arr;
	}
}

void ArrayPrinter(int *arr)
{
	int i = 0;

	for (i = SIZE_OF_ARR;i > 0; --i)
	{
		printf("%d ", *arr);
		++arr;	
	}
	printf("\n");
}

int main()
{
	int *arr = (int *)malloc(SIZE_OF_ARR * sizeof(int));
	int *res = (int *)malloc(SIZE_OF_ARR * sizeof(int));
	clock_t start = 0, end = 0;

	ArrayFiller(arr);
	start = clock();
	CountingSort(arr, SIZE_OF_ARR, (-SIZE_OF_ARR/2), ((SIZE_OF_ARR + SIZE_OF_ARR/2)-1), res);
	end = clock();	
	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);

	ArrayFiller(arr);
	start = clock();
	BubbleSort(arr, SIZE_OF_ARR);
	end = clock();	
	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);

	ArrayFiller(arr);
	start = clock();
	InsertionSort(arr, SIZE_OF_ARR);
	end = clock();	
	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);

	ArrayFiller(arr);
	start = clock();
	SelectionSort(arr, SIZE_OF_ARR);
	end = clock();	
	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);

	free(arr); arr = NULL;
	free(res); res = NULL;

	return 0;
}