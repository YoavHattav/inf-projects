#include <stdio.h>

int Bursa(int *arr, int size, int *buy, int *sell)
{
	int min = 0, current = 0, profit = 0, todays_profit = 0;
	
	while (current < size)
	{
		todays_profit = arr[current] - arr[min];

		if (arr[current] < arr[min])
		{
			min = current;
		}
		else if (profit < todays_profit)
		{
			profit = todays_profit;
			*buy = min;
			*sell = current;
		}
		
		++current;
	}

	return profit;
}

int main()
{
	int arr[] = {30, 9, 3, 1, 6, 11, 12, 13};
	int sell = 0;
	int buy = 0;
	
	printf("biggest profit is: %d\n", Bursa(arr, 8, &buy, &sell));
	printf("Bindex: %d, Sindex: %d\n", buy, sell);
	
	return 0;
} 
