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
#include <assert.h>

#include "sorts.h"

void BubbleSort(int *arr, size_t size)
{
	int swap_flag = 1;
	size_t i = 0, j = 0;
	int swap_temp = 0;

	while (swap_flag)
	{
		swap_flag = 0;

		for (i = 0;i < (size - j - 1);++i)
		{
			if (arr[i] > arr[i + 1])
			{
				swap_temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = swap_temp;

				swap_flag = 1;
			}
		}
		++j;
	}
}

void InsertionSort(int *arr, size_t size)
{
	size_t i = 0, j = 1;
	int swap_temp = 0;

	while (j < size)
	{
		swap_temp = arr[j];

		i = j;
		while (i > 0 && arr[i-1] > swap_temp)
		{
			arr[i] = arr[i-1];
			--i;
		}
		arr[i] = swap_temp;
		++j;
	}
}

void SelectionSort(int *arr, size_t size)
{
	size_t i = 0, j = 0;
	int swap = 0, min_index = 0;

	while (i < size - 1)
	{
		j = i;
		while (j < size)
		{
			if (arr[min_index] > arr[j])
			{
				min_index = j;
			}
			++j;
		}
		if (arr[i] > arr[min_index])
		{
			swap = arr[i];
			arr[i] = arr[min_index];
			arr[min_index] = swap;
		}
		++i;
	}
}

int CountingSort(const int *arr, size_t size, int min, int max, int *res)
{

	int *sum_arr = NULL;
	size_t i = 0, range = ((max - min) + 1);
	int holder = 0;

	assert(NULL != arr);

	sum_arr = calloc(range, sizeof(int));
	if (NULL == sum_arr)
	{
		return 1;
	}
	
	for (i = 0; i < size; ++i)
	{
		++sum_arr[arr[i] - min];
	}
	
	for (i = 1; i < range; ++i)
	{
		sum_arr[i] += sum_arr[i -1]; 
	}

	for (i = (size - 1); i > 0; --i)
	{
		holder = arr[i];
		res[sum_arr[arr[i] - min] - 1] = holder;
		--sum_arr[arr[i] - min];
	}

	holder = arr[i];
	res[sum_arr[arr[i] - min] - 1] = holder;

	free(sum_arr); sum_arr = NULL;
	return 0;
}

