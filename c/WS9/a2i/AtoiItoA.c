#include <stdio.h> 
#include <string.h>


int MyAtoi(char *str) 
{ 
    int num = 0;
  	
    while ('\0' != *str) 
    {	
        num = num * 10 + *str - 48;
        ++str;
  	}

    return num; 
} 

void StringVerse(char *str)
{
	char *runstart = str;
	char *runend = str + strlen(str) -1;
	int swapaid = 0;
	
	while (runstart < runend)
	{
		swapaid = *runend;
		*runend = *runstart;
		*runstart = swapaid;
		++runstart;
		--runend;
	}
}

char *MyItoa(int num, char* stri2a, int base)
{
	int negflag = 0;
	char* str = stri2a;

	if (0 > num)
	{
		negflag = 1;
		num *= -1;
	}
	if (0 == num)
	{
		*str = 48;
		*(str+1) = '\0';
		return str;
	}
	while (0 != num)
	{
		int modul = num%base;
		if (9 < modul)
		{
			*str = modul + 55;
			++str;
			num /= base;
		}
		else 
		{
			*str = modul + 48;
			++str;
			num /= base;
		}
	}
	if (1 == negflag)
	{
		*str = '-';
	}
	StringVerse(stri2a);

	return stri2a;
}





/*int main() 
{ 
	char str[100]; 
	cout << "Base:10 " << itoa(1567, str, 10) << endl; 
	cout << "Base:10 " << itoa(-1567, str, 10) << endl; 
	cout << "Base:2 " << itoa(1567, str, 2) << endl; 
	cout << "Base:8 " << itoa(1567, str, 8) << endl; 
	cout << "Base:16 " << itoa(1567, str, 16) << endl; 
	return 0; 
} */


int main() 
{ 
    /*char stratoi[] = "121223233434"; 
    int num = MyAtoi(stratoi); 
    printf("%d\n", num); */

    int itoa = 1234;
    char stritoa[30] = {0};
    int base = 2;
   
    printf("%s\n", MyItoa(itoa, stritoa, base));


    return 0; 
} 
