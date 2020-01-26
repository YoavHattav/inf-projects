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
		*arr = ((rand()%(SIZE_OF_ARR * 8 + 1)));
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

void MinMax(int *arr, size_t size, int *min, int *max)
{
	size_t i = 0;

	*min = arr[0];
	*max = arr[0];

	for (i = 1; i < size; ++i)
	{
		if (*min > arr[i])
		{
			*min = arr[i];
		}
		else if (*max < arr[i])
		{
			*max = arr[i];
		}
	}
}

int TestBubbleSort()
{
	int *arr = (int *)malloc(SIZE_OF_ARR * sizeof(int));
	int *res = (int *)malloc(SIZE_OF_ARR * sizeof(int));
	clock_t start = 0, end = 0;

	ArrayFiller(arr);
	start = clock();
	BubbleSort(arr, SIZE_OF_ARR);
	end = clock();	
	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);

	free(arr); arr = NULL;
	free(res); res = NULL;

	return 0;
}

int TestInsertionSort()
{
	int *arr = (int *)malloc(SIZE_OF_ARR * sizeof(int));
	int *res = (int *)malloc(SIZE_OF_ARR * sizeof(int));
	clock_t start = 0, end = 0;

	ArrayFiller(arr);
	start = clock();
	InsertionSort(arr, SIZE_OF_ARR);
	end = clock();	
	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);

	free(arr); arr = NULL;
	free(res); res = NULL;

	return 0;
}

int TestSelectionSort()
{
	int *arr = (int *)malloc(SIZE_OF_ARR * sizeof(int));
	int *res = (int *)malloc(SIZE_OF_ARR * sizeof(int));
	clock_t start = 0, end = 0;
	
	ArrayFiller(arr);
	start = clock();
	SelectionSort(arr, SIZE_OF_ARR);
	end = clock();	
	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);

	free(arr); arr = NULL;
	free(res); res = NULL;

	return 0;
}

int TestCountingSort()
{
	int *arr = (int *)malloc(SIZE_OF_ARR * sizeof(int));
	int *res = (int *)malloc(SIZE_OF_ARR * sizeof(int));
	clock_t start = 0, end = 0;
	int min = -SIZE_OF_ARR;
	int max = SIZE_OF_ARR;
	
	ArrayFiller(arr);
	MinMax(arr, SIZE_OF_ARR, &min, &max);

	start = clock();
	CountingSort(arr, SIZE_OF_ARR, min, max, res);
	end = clock();	

	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);

	free(arr); arr = NULL;
	free(res); res = NULL;
	
	return 0;
}

int TestRadixSort()
{
	unsigned int *arr = (unsigned int *)malloc(SIZE_OF_ARR * sizeof(int));
	unsigned int num_of_bits = 4;
	clock_t start = 0, end = 0;
	int i = 0;

	srand(time(0));
	for (i = 0; i < SIZE_OF_ARR; ++i)
	{
		arr[i] = ((rand()%(SIZE_OF_ARR * 8 + 1)));
	}

	start = clock();
	RadixSort(arr, SIZE_OF_ARR, num_of_bits);
	end = clock();

	printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);
	
	free(arr); arr = NULL;

	return 0;
}

static void TestMergeSort()
{
	int arr[] = {12, 11, 13, 5, 6};
	int temp_arr[5];
	int i = 0, arr_size = 5;
	
	MergeSort(arr, temp_arr, arr_size);

	for (; i < arr_size; ++i)
	{
		printf("%d\n", arr[i]);
	}
}

int main()
{
	/*TestBubbleSort();
	TestInsertionSort();
	TestSelectionSort();
	TestCountingSort();*/
	/*TestRadixSort();*/
	TestMergeSort();

	return 0; 
}