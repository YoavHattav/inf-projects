#include <stdio.h>
int YosefMath(int people, int jump4kill)
{
    int result=0;
    for (int i=1;i<=people;i++)
    {
        result= (result+jump4kill)%i;
    }
    return result+1;
}
int main()
{
    int peo, k;
    printf("Enter the number of prisoners! (pls):\n");
    scanf("%d", &peo);
    printf("Enter skip number! (pls):\n");
    scanf("%d", &k);
    printf("the right position to stand in is: %d", YosefMath(peo,k));

    return 0;
}

