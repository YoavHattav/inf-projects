#include <stdio.h>
#include <string.h>
#include <ctype.h>


void DeSpacer(char *instring)

{
    
    int i=0, j=0;
    int end=strlen(instring);
    while(isspace(*instring))
    {
      for(i=0;i<end;i++)
      {
          *(instring+i)=*(instring+i+1);
      }
      end-=1;
      *(instring+end-1)='\0';
    }
    for(j=0;j<end;j++)
    {
        if (isspace(*(instring+j)) && isspace(*(instring+1+j)))
            {
                for(i=j;i<end;i++)
                {
                    *(instring+i)=*(instring+i+1);
                }
                end-=1;
                --j;
            }
    }
    *(instring+end-1)='\0';
    
}
int main()
{
    char str[]="      i love it         when  im right    ";
    DeSpacer(str);
    printf("%s", (char *)str);
    printf("yalla taavod yamaniak");
    return 0;
   
}