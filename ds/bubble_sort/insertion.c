#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void ArrayFiller(int *arr)
{
	int i = 0;
	for (i = SIZE;i > 0;i--)
	{
		*arr = i;
		++arr;
	}
}

void ArrayPrinter(int *arr)
{
	int i = 0;

	for (i = SIZE;i > 0; --i)
	{
		printf("%d ", *arr);
		++arr;	
	}
	printf("\n");
}

void InsertionSorter(int arr[])
{
	int i = 0, j = 1, swap_temp = 0;

	while (j < SIZE)
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


int main()
{
	int *arr = (int *)malloc(SIZE * sizeof(int));

	ArrayFiller(arr);
	ArrayPrinter(arr);
	InsertionSorter(arr);
	ArrayPrinter(arr);

	free(arr);

	return 0;
}