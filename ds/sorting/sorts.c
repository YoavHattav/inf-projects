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

#define NUM_OF_BIT_IN_INT 32

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
		res[sum_arr[arr[i] - min] - 1] = arr[i];
		--sum_arr[arr[i] - min];
	}

	res[sum_arr[arr[i] - min] - 1] = arr[i];

	free(sum_arr); sum_arr = NULL;

	return 0;
}

static void RadixCountingSort(unsigned int *src,
							 unsigned int *dest,
							 size_t *hist,
							 size_t size,
							 unsigned int mask,
							 unsigned int shift)
{	
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		++hist[(src[i]>>shift) & mask];
	}

	for(i = 1; i < (mask + 1); i++)
	{
		hist[i] += hist[i - 1];
	}
	for(i = (size - 1);0 <= (long)i; --i)
	{
		dest[hist[(src[i]>>shift) & mask] - 1] = src[i];
		--hist[(src[i]>>shift) & mask];
	}
	
}

int RadixSort(unsigned int *arr, size_t size, unsigned int num_of_bits)
{
	unsigned int mask = (1 << num_of_bits) - 1;
	unsigned int i = 0, j = 0;
	unsigned int shift = 0;
	unsigned int *swap_ptr = NULL;
	size_t *hist = NULL;
	unsigned int *res = NULL;

	assert(NULL != arr);

	hist = (size_t *)calloc((mask + 1) , sizeof(size_t));
	if (NULL == hist)
	{
		return 1;
	}
	res = (unsigned int *)malloc(size * sizeof(unsigned int));
	if (NULL == res)
	{
		free(hist); hist = NULL;
		return 1;
	}

	for (i = 0; i < (NUM_OF_BIT_IN_INT/num_of_bits); ++i)
	{
		shift = i * num_of_bits;

		RadixCountingSort(arr, res, hist, size, mask, shift);

		for (j = 0; j < (mask + 1); j++)
		{
			hist[j] = 0;
		}

		swap_ptr = arr;
		arr = res;
		res = swap_ptr;
	}

	free(hist); hist = NULL;
	free(res); res = NULL;

	return 0;
}

void Merge(int *arr, int *temp_arr, size_t size)
{
	size_t left_index = 0;
	size_t right_index = size / 2;
	size_t temp_index = 0;
 	size_t mid_index = right_index;

 	while ((right_index < size) && (left_index < mid_index))
 	{
 		if (arr[left_index] >= arr[right_index])
 		{
 			temp_arr[temp_index] = arr[right_index];
 			++right_index;
 			++temp_index;
 		}

 		else
 		{
 			temp_arr[temp_index] = arr[left_index];
 			++left_index;
 			++temp_index;
 		}
 	}

 	while (right_index < size)
 	{
		temp_arr[temp_index] = arr[right_index];
		++right_index;
		++temp_index;
 	}

 	while (left_index < mid_index)
 	{
		temp_arr[temp_index] = arr[left_index];
 		++left_index;
 		++temp_index;
 	}

 	for (temp_index = 0; temp_index < size; ++temp_index)
 	{
 		arr[temp_index] = temp_arr[temp_index];
 	}
}

void MergeSort(int *src_arr, int *temp_arr, size_t size)
{
	size_t mid_point = size / 2;

	if (size < 2)
	{
		return;
	}

	MergeSort(src_arr, temp_arr, mid_point);
	MergeSort(src_arr + mid_point , temp_arr, size - mid_point);

	Merge(src_arr, temp_arr, size);
}

