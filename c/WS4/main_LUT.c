#include <stdio.h>
#include <stdlib.h>
#include "LUT_of_funcs.h"
/********************************/
/*	Yoav Hattav			        */
/*	11.11.19		        	*/
/*	LUT of Fun       			*/
/*								*/
/*	Reviewer: Shye The Presser	*/
/********************************/


int main()
{
	int (*LUT[256])(char);

	CreatLUT(LUT);
	USELUT(LUT);

	return 0;
}