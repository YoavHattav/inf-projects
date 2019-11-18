#include <stdio.h>
#include "bitwisefuncs.h"

int main()
{
	unsigned int array[MAX];
	unsigned int n = 0, x = 0, y = 0;
	long result1 = 0;
	int result2 = 0, result3 = 0;
	int a = 1, i=0;
 	unsigned int *px = &x;
 	unsigned int *py = &y;
 	unsigned char ch = 0;

	switch (choice)
	{
		case(1):
			scanf("%u%u", &x, &y);
			result1 = Pow2(x, y);
			printf("%ld\n", result1);
			Test(Pow2(12, 12) == 49152, "simple true");
			Test(Pow2(12, ) == 0, "empty number");
			Test(Pow2(12, 12) == 1, "simple false");
			Test(Pow2(5, 4) == 80, "another true");


		case (2):
		{}
			scanf("%u", &n);
			result2 = IsItpow2(n);
			printf("%d\n", result2);
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");


		case(3):
			scanf("%u", &n);
			result3 = IsItpow2p2(n);
			printf("%d\n", result3);
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");


		case(4):
			printf("enter a number for \"addone\"\n"); 
			scanf("%d", &a);
			a = AddOne(a);
			printf("%d\n", a);
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");


		case(5):
			printf("enter numbers for the array\n");
			for (i = 0; i < MAX ; i++)
			{
				scanf("%u", &array[i]);
			}
			ThreeOn(array);
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");


		case(6):
			printf("enter a number for HowManySet\n");
			scanf("%d", &a);
			a = HowManySet(a);
			printf("%d\n", a);
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");


		case(7):
			printf("enter two numbers for Swap\n");
			scanf("%u%u", &x, &y);
			Swap(px, py);
			printf("numbers after swap are x:%u y:%u\n", x, y);
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");

		  
		case(8):
			printf("enter a number for Mirror\n");
			scanf("%u", &n);
			x = ByteMirror(n);
			printf("mirror to ur num is: %d\n", x);
			printf("in bits:\n");
			ShowBits(x);   
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");

		               
		case (9):
		 	printf("enter a number for Closest\n");
		 	scanf("%u", &x);
			x = Closest(x);
			printf("%u\n", x);  
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");

		        
		case(10):
		 	printf("enter a number for 3>5>3\n");
			scanf("%d", &ch);
			ch = SwapThirdAndFifth(ch);
			printf("%d\n", ch);
			printf("in bits:\n");
			ShowBits(ch); 
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");


		case(11):
			printf("enter a number for 2&6\n");
			scanf("%d", &ch);
			printf("%d\n", BothTwoAndSix(ch));
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");


		case(12):
			printf("enter a number for 2|6\n");
			scanf("%d", &ch);
			printf("%d\n", OneOfTwoAndSix(ch));
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");

		case(13):
			printf("enter a number for Bit count no loop\n");
			scanf("%d", &x);
			printf("%d\n", SetBitCounter(x));
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");

		    

		case(14):
			printf("enter a number for MirrorNoLoop\n");
			scanf("%u", &n);
			x = ByteMirror(n);
			printf("mirror to ur num is: %d\n", x);
			printf("in bits:\n");
			ShowBits(x); 
			Test(IsRotate("abc", "bca") == 1, "simple false");
			Test(IsRotate("abc", "bca") == 0, "simple true");
			Test(IsRotate("", "bca") == 1, "simple false-empty string");
			Test(IsRotate("abc", "bca") == 1, "simple false");
	}



	return 0;
}
