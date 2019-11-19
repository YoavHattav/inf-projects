#include <stdio.h>

char *Mystrcat(char *dest_cat, const char *sour_cat)
{
    char *runner=dest_cat;
    while('\0' != *dest_cat)
    {
        ++dest_cat;
    }
    while ('\0' != *sour_cat)
    {
        *dest_cat = *sour_cat;
        ++sour_cat;
        ++dest_cat;
    }
    return runner;
}
int main()
{
const char sour[50]="when she's gone..";
char dest[50]="aint no sunshine ";
Mystrcat(dest, sour);
printf("%s", dest);
return 0;
}
