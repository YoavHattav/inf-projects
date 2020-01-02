#include <string.h>
#include <stdio.h>
#include <assert.h>

int main()
{
	int a = 100;
	void *p = NULL;
	FILE *fp = NULL;

	fp = fopen("file.txt", "w");

	fscanf(fp, "%p", &p);

	printf("%d", *(int *)p);

    fclose(fp); 

	return 0;
}

