#include <stdio.h>
#include "bitwisefuncs.h"

int main()
{
	unsigned n = 0, x = 0, y = 0;
	long result1 = 0;
	int result2 = 0, result3 = 0;
	


	scanf("%u%u", &x, &y);
	result1 = Pow2(x, y);
	printf("%ld\n", result1);

	scanf("%u", &n);
	result2 = IsItpow2(n);
	printf("%d\n", result2);

	scanf("%u", &n);
	result3 = IsItpow2p2(n);
	printf("%d\n", result3);

	return 0;
}
