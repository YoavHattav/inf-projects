#include <stdio.h>


void Boom(int from, int to)
{
    int i=from, bflag=0;
    int mnum, temp=0;
    for( i=from ; i<to ; i++ ) 
    {
        if (0 == (i%7))
        {
            bflag=1;
        }
        mnum=i;
        while(mnum>0)
        {
            temp=mnum%10;
            if(7==temp)
            {
                bflag=1;
            }
            mnum/=10;
        }
        
        if(1==bflag)
        {
            printf("BOOM\n");
        }
        else
        {
            printf("%d\n", i);
        }
        bflag=0;
    }
    
}
int main()
{
    int a, b;
    printf("enter the From and To nums:\n");
    scanf("%d%d", &a, &b);
    Boom(a, b);
    return 0;
}
