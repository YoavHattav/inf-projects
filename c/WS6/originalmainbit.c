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

	
	scanf("%u%u", &x, &y);
	result1 = Pow2(x, y);
	printf("%ld\n", result1);
			
	scanf("%u", &n);
	result2 = IsItpow2(n);
	printf("%d\n", result2);
			
	scanf("%u", &n);
	result3 = IsItpow2p2(n);
	printf("%d\n", result3);
			
	printf("enter a number for \"addone\"\n"); 
	scanf("%d", &a);
	a = AddOne(a);
	printf("%d\n", a);
			
	printf("enter numbers for the array\n");
	for (i = 0; i < MAX ; i++)
	{
		scanf("%u", &array[i]);
	}
	ThreeOn(array);
			
	printf("enter a number for HowManySet\n");
	scanf("%d", &a);
	a = HowManySet(a);
	printf("%d\n", a);
			
	printf("enter two numbers for Swap\n");
	scanf("%u%u", &x, &y);
	Swap(px, py);
	printf("numbers after swap are x:%u y:%u\n", x, y);
		
	printf("enter a number for Mirror\n");
	scanf("%u", &n);
	x = ByteMirror(n);
	printf("mirror to ur num is: %d\n", x);
	printf("in bits:\n");
	ShowBits(x);   
			
	printf("enter a number for Closest\n");
	scanf("%u", &x);
	x = Closest(x);
	printf("%u\n", x);  
			
	printf("enter a number for 3>5>3\n");
	scanf("%d", &ch);
	ch = SwapThirdAndFifth(ch);
	printf("%d\n", ch);
	printf("in bits:\n");
	ShowBits(ch); 
			
	printf("enter a number for 2&6\n");
	scanf("%d", &ch);
	printf("%d\n", BothTwoAndSix(ch));
			
	printf("enter a number for 2|6\n");
	scanf("%d", &ch);
	printf("%d\n", OneOfTwoAndSix(ch));
			
	printf("enter a number for Bit count no loop\n");
	scanf("%u", &x);
	printf("%d\n", SetBitCounter(x));
			
	printf("enter a number for MirrorNoLoop\n");
	scanf("%u", &n);
	x = ByteMirror(n);
	printf("mirror to ur num is: %d\n", x);
	printf("in bits:\n");
	ShowBits(x); 
			
	
	return 0;
}
