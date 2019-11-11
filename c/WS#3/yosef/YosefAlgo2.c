#include <stdio.h>

#define Yalla 1000

int YosefAlgo(int people, int counter)
{
	int i =0;
	int winner=0;
	int arr[Yalla];
	int alive = people;

	for ( ; i<people;i++)
	{
	arr[i]= 1;
	}
	while(1 < alive)
	{
		winner=counter;
		++counter;
		/*findint next alive*/
		while(1 != arr[counter])
		{
			++counter;

			if(people <= counter)
			{
				counter=0;
			}
		}

		arr[counter] = 0;
		--alive;
		/*findint next alive*/
		while(1 != arr[counter])
		{
			++counter;
			if(people <= counter)
			{
				counter=0;
			}
		}
	}

	return winner;
}

int main()
{
	int people = 0, first = 0;

	printf("Enter the number of prisoners pls:\n");
	scanf("%d", &people);
	printf("Enter the first to hold the sword! and let the game begin\n");
	scanf("%d", &first);
	printf("And the Position to stand in to live is: %d\n", YosefAlgo(people, first));

	return 0;
}