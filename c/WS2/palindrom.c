#include <stdio.h>
#include <string.h>

int IsitaPalindrome(char *str)
{
    char *runner1= str , *runner2= (str+strlen(str)-1);
    while (runner2 > runner1)
    {
        if(*runner2 != *runner1)
        {
            printf("not a Palindrome");
            return 0;
            break;
        }
        ++runner1;
        --runner2;
    }
    return 1;
}

int main()
{
    int flag=1;
    char *isit={"12345544321"};
    flag=IsitaPalindrome(isit);
    (flag==0) ? printf("no") : printf("YeS!");
    return 0;
}