#include <stdio.h>

int YosefAlgo(int people)
{
    char arr[people];
    int alive=people;
    int i=0,j=1;
    for(i=0;i<people;i++)
    {
        arr[i]='A';
    }
    while( 1 < alive )
    {
        for(i=j;i<people;i++)
        {
            if ('A'== arr[i])
            {
                arr[i]='D';
                printf("person number %d has been killed\n", i);
                --alive;
                j=i;
                break;
            }
        }
        for(j=i;j<people;j++)
        {
           if ('A'== arr[i])
            {
                ++j;
                break;
            } 
        }
        if(j==(people-1) || j==people)
        {
            j=0;
        }
    }
    for(i=0;i<people;i++)
    {
        if('A'==arr[i])
        {
            printf("%d is alive!", i);
        }
    }
    return 0;
}
int main()
{
	int people=20;
	YosefAlgo(people);
}
