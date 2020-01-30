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
#define UNUSED(x) (void)(x)

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
	int arr[] = {10, 80, 30, 90, 40, 50, 70};
	int temp_arr[7];
	int i = 0, arr_size = 7;
	
	MergeSort(arr, temp_arr, arr_size);

	for (; i < arr_size; ++i)
	{
		printf("%d\n", arr[i]);
	}
}
static int UserCompare_QuickSort(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

static void TestQuickSort()
{
	int arr[] = {80, 10};
	int i = 0;
	size_t elem_size = 4;
	size_t arr_size = 2;
	
	QuickSort(arr, arr_size, elem_size, &UserCompare_QuickSort);

	for (; i < arr_size; ++i)
	{
		printf("%d\n", arr[i]);
	}
}

static int UserCompare_BinnarySearch(const void *data1, const void *data2, const void *param)
{
	UNUSED(param);

	return (*(int *)data1 - *(int *)data2);
}

static void TestBinarySearch()
{
	int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
	int i = 0, x = 80;
	size_t elem_size = 4;
	size_t arr_size = 9;
	
	void *result = NULL;

	result = BinarySearch(arr, elem_size, arr_size, &UserCompare_BinnarySearch, &x, NULL);

	if (NULL != result)
	{
		printf("%d\n", *(int *)result);
	}
}

static void TestJumpSearch()
{
	int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
	int i = 0, x = 90;
	size_t elem_size = 4;
	size_t arr_size = 9;
	
	void *result = NULL;

	result = JumpSearch(arr, elem_size, arr_size, &UserCompare_BinnarySearch, &x, NULL);

	if (NULL != result)
	{
		printf("%d\n", *(int *)result);
	}
}

int main()
{
	/*TestBubbleSort();
	TestInsertionSort();
	TestSelectionSort();
	TestCountingSort();*/
	/*TestRadixSort();
	TestMergeSort();*/
	/*TestQuickSort();*/
	TestBinarySearch();
	TestJumpSearch();

	return 0; 
}