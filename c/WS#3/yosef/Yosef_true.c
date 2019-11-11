#include <stdio.h>

int Jos();


int main()
{
   
   int last;
   
   last = Jos();
   
   printf("last: %d\n", last);
   return 0;
}


int Jos()
{
   int a[150];
   int i = 0;
   
   /* initialize the array */
   while (i < 150 - 1)
   {
      a[i] = i + 1;
      ++i;
   }
   
   a[i] = 0;
   
   i = 0;
   
   /* kill and move the index to the next alive */ 
   while (a[i] != i)
   {
      a[i] = a[a[i]];
      i = a[i];
   }
   
   return i + 1;
}
