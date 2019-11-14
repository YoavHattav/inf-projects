/********************************/
/*	Yoav Hattav			        */
/*	13.11.19		        	*/
/*	Files and strings       	*/
/*								*/
/*	Reviewer: Raz the slayer	*/
/********************************/


#include <stdio.h>
#include <string.h>
#include "ws5funcs.h"


int main()
{
	chain op[5];
	char filename[MAX];

	printf("Pls enter ur filename.\n");
	fgets(filename, MAX, stdin);

	initiate(op);
	Infrastructure(filename, op);

	return 0;
}