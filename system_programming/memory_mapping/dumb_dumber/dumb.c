#include <string.h>
#include <stdio.h>
#include <assert.h>

int main()
{
	int a = 200;
	void *p = &a;

	FILE *fp = NULL;


	fp = fopen("file.txt", "w");
	fprintf(fp, "%p", p);


    fclose(fp); 
	
	return 0;
}

