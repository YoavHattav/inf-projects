#include <stdio.h>

int bit_return(int a, int loc)   
{
    int buf = a & 1<<loc;

    if (buf == 0) return 0;
    else return 1; 
}

int main() 
{
    
    float a = -2.25; 

    int i;
    unsigned int *b;
    b = (unsigned int*)(&a);

    
    for (i = 31; i >= 0; i--)
    {
        printf("%d",bit_return(*b,i));
    }
    printf("\n");

    return 0;
}