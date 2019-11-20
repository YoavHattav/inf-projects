#include <stdio.h>
#define MAX2(a, b) 12 == a*b ? a*b : a/b
#define MAX3(a, b, c) \
						if (a > b && c > b) \
						{\
						printf("go home!\n"); \
						} \
							else\
							{\
							printf("Keep studing...\n"); \
							};
#define VAR_SIZE(x)  ((char*)(&x+1)-(char*)(&x))
#define TYPE_SIZE(type) (size_t)(((type*)0)+1)


int main()
{
	
	int x = MAX2(3, 4);
	printf("%d\n", x);
	MAX3(5, 4, 3)
	printf("%ld\n", VAR_SIZE(x));;
	printf("%ld\n", TYPE_SIZE(int));;

	return 0;
}