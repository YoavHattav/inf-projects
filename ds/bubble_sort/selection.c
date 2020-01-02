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

void SelectionSorter(int arr[])
{
	int i = 0, j = 1, swap_min = 0;

	while (i < SIZE - 1)
	{
		j = i;
		while (j < SIZE)
		{
			if (arr[i] > arr[j])
			{
				swap_min = arr[i];
				arr[i] = arr[j];
				arr[j] = swap_min;
			}
			++j;
		}
		++i;
	}
}


int main()
{
	int *arr = (int *)malloc(SIZE * sizeof(int));

	ArrayFiller(arr);
	ArrayPrinter(arr);
	SelectionSorter(arr);
	ArrayPrinter(arr);

	free(arr);

	return 0;
}