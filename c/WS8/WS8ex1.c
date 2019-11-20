#include <stdio.h>
#include <string.h>
#include "WS8ex1.h"




typedef struct  mycreation 
{
	void *data;
	void (*Pprint)(const void *data);
	void (*Padd)(void *data, int x);
	int (*Pclean)(void *data);

}FourPStruct;


void PrintInt(const void* data)
{
	printf("%d\n", *((int*)&data));
}

void PrintFloat(const void *data)
{
	printf("%f\n", *((float*)&data));
}

void PrintStr(const void *data)
{
	printf("%s\n", (char*)data);
}

void AddInt(void* data, int x)
{
	
	*((int*)(data)) += x;
}

void AddFloat(void* data, int x)
{
	
	*((float*)(data)) += x;
}
/*int CountDigits(int x)
{
	int counter = 0;
	int n = x;
	while (0 != n)
	{
		++counter;
		n /= 10;
	}

	return counter;
} */

void AddToStr(void *data, int x)
{
	
	int len = strlen(*(char**)data);
	int counter = 0;  /*CountDigits(x); */
	char str[SIZEOFSTR];

	*(char **)data = (void *)realloc(*(char **)data, (len+counter +1));

	sprintf(str, "%d", x);
	strcat(*(char **)data, str);  /*make a terminator*/


}

int Clean(void* data)
{
	free(data); data = NULL;

	return SUCC;
}

int CleanNothing(void* data)
{
	UNUSED(data);
	return 0;
}

void init(FourPStruct arr[])
{
	arr[3].data = malloc (SIZEOFSTR);
	if (NULL == arr[3].data)
	{ 
        printf("Memory not allocated.\n"); 
        exit(0);
    } 
	

	*((int*)(&arr[1].data)) = 21;
	arr[1].Pprint = &PrintInt;
	arr[1].Padd = &AddInt;
	arr[1].Pclean = CleanNothing;

	*((float*)(&arr[2].data)) = 3.14;
	arr[2].Pprint = &PrintFloat;
	arr[2].Padd = &AddFloat;
	arr[2].Pclean = CleanNothing;

	strcpy(arr[3].data,"Lets Gooo home!");
	arr[3].Pprint = &PrintStr;
	arr[3].Padd = &AddToStr;   
	arr[3].Pclean = &Clean;

}

/* the brain of the algorithm */
void InfraS(FourPStruct arr[])
{
	int i = 1;
	
	int x = 1;
	
	while (0 != x) 
	{
		printf("Pls enter a num 2 add\n");
		scanf("%d", &x);

	
		for ( i = 1 ; i < SIZE ; i++ )
		{
			arr[i].Pprint(arr[i].data);
			arr[i].Padd(&(arr[i].data), x);
			arr[i].Pprint(arr[i].data);
			arr[i].Pclean(arr[i].data);
		}
	}
	exit(0);
}


int main()
{
	FourPStruct arr[3];

	init(arr);
	InfraS(arr);

	printf("oyoyoyoyoo\n");
	return 0;
}
