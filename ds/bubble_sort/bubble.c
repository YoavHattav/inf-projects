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

void BubbleSorter(int arr[])
{
	int swap_flag = 1;
	int i = 0, swap_temp = 0;

	while (swap_flag)
	{
		swap_flag = 0;

		for (i = 0;i < (SIZE - 1);++i)
		{
			if (arr[i] > arr[i + 1])
			{
				swap_temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i+1] = swap_temp;

				swap_flag = 1;
			}
		}
	}
}


int main()
{
	int *arr = (int *)malloc(SIZE * sizeof(int));

	ArrayFiller(arr);
	ArrayPrinter(arr);
	BubbleSorter(arr);
	ArrayPrinter(arr);

	free(arr);

	return 0;
}