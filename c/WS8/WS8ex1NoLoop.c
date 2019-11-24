#include "WS8ex1.h"

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

void AddToStr(void *data, int x)
{
	
	int len = strlen(*(char**)data);
	int counter = 0; 
	int n = x; 
	char str[SIZEOFSTR];
	while(0 != n)
	{
		++counter;
		n /= 10;
	}

	*(char **)data = (void *)realloc(*(char **)data, (len+counter +1));

	sprintf(str, "%d", x);
	strcat(*(char **)data, str); 
}

int Clean(void* data)
{
	free(data); data = NULL;

	return 0;
}

int CleanNothing(void* data)
{
	UNUSED(data);
	return 0;
}

void init(FourPStruct arr[])
{
	*((int*)(&arr[1].data)) = 21;
	arr[1].Pprint = PrintInt;
	arr[1].Padd = AddInt;
	arr[1].Pclean = CleanNothing;

	*((float*)(&arr[2].data)) = 3.14;
	arr[2].Pprint = PrintFloat;
	arr[2].Padd = AddFloat;
	arr[2].Pclean = CleanNothing;
	
	arr[3].Pprint = PrintStr;
	arr[3].Padd = AddToStr;   
	arr[3].Pclean = Clean;
	arr[3].data = (char *)malloc(SIZEOFSTR);
	if (NULL == arr[3].data)
	{ 
        printf("Memory not allocated.\n"); 
        return;
    } 
    strcpy(arr[3].data,"Lets Gooo home!");
}

/* the brain of the algorithm */
void InfraS(FourPStruct arr[])
{
	int i = 1;
	int x = 6;
	
	for ( i = 1 ; i < SIZE_ARR ; i++ )
	{
		arr[i].Pprint(arr[i].data);
		arr[i].Padd(&(arr[i].data), x);
		arr[i].Pprint(arr[i].data);
		arr[i].Pclean(arr[i].data);
	}
}


int main()
{
	static FourPStruct arr[3];

	init(arr);
	InfraS(arr);

	return 0;
}
