
#include <stdio.h>


void PSwap(int **a, int **b)
{
    printf("x is %p\n y is %p\n", *a, *b);
    int **temp;
    *temp = *a;
    *a = *b;
    *b = *temp;
    printf("after\n x is %p\n y is %p\n", *a, *b);
}



  
int main()
{
   int x=2, y=3;
   int *ap;
   int *bp;
   ap=&x;
   bp=&y;
  
   PSwap(&ap, &bp);
   

    return 0;
}

