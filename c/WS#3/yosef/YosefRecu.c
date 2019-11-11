#include <stdio.h>

int YosefRecu(int people, int jump)
{
    return people > 1 ? (YosefRecu(people-1, jump)+jump-1)%people+1 : 1;
}
int main()
{
    int peo, k;
    printf("Enter the number of prisoners! (pls):\n");
    scanf("%d", &peo);
    printf("Enter skip number! (pls):\n");
    scanf("%d", &k);
    printf("the right position to stand in is: %d", YosefRecu(peo,k));

    return 0;
}
